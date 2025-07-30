// Реализация клавиатуры
// Клавиатура подключена к порту 0x60

// Реализация клавиатуры:
// - Инициализация клавиатуры через функцию keyboard_init через функцию outb и проверку, готова ли клавиатура через функцию keyboard_has_data
// - Чтение скан-кода клавиши через функцию keyboard_read_scancode через функцию inb и проверку, есть ли данные в буфере через функцию keyboard_has_data и проверку, есть ли данные в буфере через функцию keyboard_has_data
// - Преобразование скан-кода в ASCII через функцию keyboard_scancode_to_ascii через проверку, нажата ли клавиша Shift через функцию keyboard_is_shift_pressed и проверку, нажата ли клавиша Ctrl через функцию keyboard_is_ctrl_pressed и проверку, нажата ли клавиша Alt через функцию keyboard_is_alt_pressed и проверку, нажата ли клавиша Caps Lock через функцию keyboard_is_caps_lock и проверку, что это не специальная клавиша и не отпускание
// - Обработка ввода через функцию keyboard_handle_input через функцию keyboard_read_scancode и проверку, нажата ли клавиша Shift через функцию keyboard_is_shift_pressed и проверку, нажата ли клавиша Ctrl через функцию keyboard_is_ctrl_pressed и проверку, нажата ли клавиша Alt через функцию keyboard_is_alt_pressed и проверку, нажата ли клавиша Caps Lock через функцию keyboard_is_caps_lock и проверку, что это не специальная клавиша и не отпускание
// - Добавление символа в буфер через функцию keyboard_buffer_put через глобальную переменную keyboard_state.buffer и проверку, заполнен ли буфер через функцию keyboard_state.count < KEYBOARD_BUFFER_SIZE
// - Извлечение символа из буфера через функцию keyboard_buffer_get через глобальную переменную keyboard_state.buffer и проверку, пуст ли буфер через функцию keyboard_state.count > 0
// - Проверка, пуст ли буфер через функцию keyboard_buffer_empty 
// - Получение символа из буфера через функцию keyboard_get_char через функцию keyboard_buffer_get и проверку, пуст ли буфер через функцию keyboard_buffer_empty
// - Проверка, есть ли данные в буфере через функцию keyboard_has_data через функцию keyboard_buffer_empty и проверку, пуст ли буфер через функцию keyboard_buffer_empty
// - Проверка, нажата ли клавиша Shift через функцию keyboard_is_shift_pressed через глобальную переменную keyboard_state.shift_pressed
// - Проверка, нажата ли клавиша Ctrl через функцию keyboard_is_ctrl_pressed через глобальную переменную keyboard_state.ctrl_pressed
// - Проверка, нажата ли клавиша Alt через функцию keyboard_is_alt_pressed через глобальную переменную keyboard_state.alt_pressed
// - Проверка, нажата ли клавиша Caps Lock через функцию keyboard_is_caps_lock через глобальную переменную keyboard_state.caps_lock

// Функции для работы с буфером:
// - keyboard_buffer_put - добавление символа в буфер
// - keyboard_buffer_get - извлечение символа из буфера
// - keyboard_buffer_empty - проверка, пуст ли буфер
// - keyboard_get_char - получение символа из буфера
// - keyboard_has_data - проверка, есть ли данные в буфере

// Функции для работы с модификаторами:
// - keyboard_is_shift_pressed - проверка, нажата ли клавиша Shift
// - keyboard_is_ctrl_pressed - проверка, нажата ли клавиша Ctrl
// - keyboard_is_alt_pressed - проверка, нажата ли клавиша Alt
// - keyboard_is_caps_lock - проверка, нажата ли клавиша Caps Lock

// Здесь используются прерывания. Потому что, оказывается, это быстрее, чем использовать буферы.
// А есть еще что-то типа кадрового буфера для ввода-вывода?
// Да, есть. Это буфер клавиатуры.
// Буфер клавиатуры - это буфер, в который записываются скан-коды клавиш, которые нажаты.
// Я могу использовать буфер клавиатуры для работы с клавиатурой. Но это медленно и неэффективно. Плюс могут быть потери данных.
// Поэтому я использую прерывания.

// FecalOS Keyboard Driver
// Author: KillerGrass

#include "keyboard.h"

// глобальное состояние клавиатуры
static keyboard_state_t keyboard_state;

// таблица преобразования скан-кодов в ASCII (без Shift)
static const char scancode_to_ascii_table[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
    0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0
};

// таблица преобразования скан-кодов в ASCII (с Shift)
static const char scancode_to_ascii_shift_table[] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0,
    0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0
};

// функция для чтения из порта
static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// функция для записи в порт
static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

// инициализируем клавиатуру
void keyboard_init(void) {
    keyboard_state.head = 0;
    keyboard_state.tail = 0;
    keyboard_state.count = 0;
    keyboard_state.shift_pressed = 0;
    keyboard_state.ctrl_pressed = 0;
    keyboard_state.alt_pressed = 0;
    keyboard_state.caps_lock = 0;
    
    // очищаем буфер
    for (int i = 0; i < KEYBOARD_BUFFER_SIZE; i++) {
        keyboard_state.buffer[i] = 0; // заполняем буфер нулями
    }
    
    // отправляем команду сброса клавиатуры
    outb(PS2_COMMAND_PORT, 0xAD); // отключаем первую клавиатуру
    outb(PS2_COMMAND_PORT, 0xAE); // включаем первую клавиатуру
    
    // ждем готовности
    while (inb(PS2_COMMAND_PORT) & 0x02);
    
    // устанавливаем тип сканирования
    outb(PS2_DATA_PORT, 0xF0); // устанавливаем тип сканирования
    outb(PS2_DATA_PORT, 0x01); // устанавливаем тип сканирования 1
    
    vga_print_text(0, 24, "Keyboard initialized", VGA_LIGHT_GREEN); // выводим сообщение о том, что клавиатура инициализирована
}

// читаем скан-код клавиши
unsigned char keyboard_read_scancode(void) {
    // ждем, пока есть данные
    while (!(inb(PS2_COMMAND_PORT) & 0x01));
    return inb(PS2_DATA_PORT);
}

char keyboard_scancode_to_ascii(unsigned char scancode) {
    // проверяем, что скан-код в допустимом диапазоне
    if (scancode >= sizeof(scancode_to_ascii_table)) {
        return 0;
    }
    
    // определяем, какую таблицу использовать
    const char* table = (keyboard_state.shift_pressed || 
                        (keyboard_state.caps_lock && scancode >= 0x10 && scancode <= 0x1B)) 
                        ? scancode_to_ascii_shift_table 
                        : scancode_to_ascii_table;
    
    return table[scancode];
}

void keyboard_handle_input(void) {
    unsigned char scancode = keyboard_read_scancode();
    
    // обрабатываем специальные клавиши
    switch (scancode) {
        case KEY_LSHIFT:
        case KEY_RSHIFT:
            keyboard_state.shift_pressed = 1;
            break;
        case KEY_LSHIFT | KEY_RELEASE:
        case KEY_RSHIFT | KEY_RELEASE:
            keyboard_state.shift_pressed = 0;
            break;
        case KEY_CTRL:
            keyboard_state.ctrl_pressed = 1;
            break;
        case KEY_CTRL | KEY_RELEASE:
            keyboard_state.ctrl_pressed = 0;
            break;
        case KEY_ALT:
            keyboard_state.alt_pressed = 1;
            break;
        case KEY_ALT | KEY_RELEASE:
            keyboard_state.alt_pressed = 0;
            break;
        case KEY_CAPS_LOCK:
            keyboard_state.caps_lock = !keyboard_state.caps_lock;
            break;
        default:
            // если это не специальная клавиша и не отпускание
            if (!(scancode & KEY_RELEASE)) {
                char ascii = keyboard_scancode_to_ascii(scancode);
                if (ascii) {
                    keyboard_buffer_put(ascii);
                }
            }
            break;
    }
}

// Добавляет символ в буфер
void keyboard_buffer_put(unsigned char c) {
    if (keyboard_state.count < KEYBOARD_BUFFER_SIZE) { // если буфер не заполнен
        keyboard_state.buffer[keyboard_state.head] = c; // добавляем символ в буфер
        keyboard_state.head = (keyboard_state.head + 1) % KEYBOARD_BUFFER_SIZE; // обновляем указатель на голову
        keyboard_state.count++; // увеличиваем счетчик
    }
}

// Извлекает символ из буфера
unsigned char keyboard_buffer_get(void) {
    if (keyboard_state.count > 0) { // Если буфер не пуст
        unsigned char c = keyboard_state.buffer[keyboard_state.tail]; // извлекаем символ из буфера
        keyboard_state.tail = (keyboard_state.tail + 1) % KEYBOARD_BUFFER_SIZE; // обновляем указатель на хвост
        keyboard_state.count--; // уменьшаем счетчик
        return c; // возвращаем извлеченный символ
    }
    return 0; // если буфер пуст
}

// проверяет, пуст ли буфер
int keyboard_buffer_empty(void) {
    return keyboard_state.count == 0; // возвращает true, если буфер пуст
}

// получает символ из буфера
char keyboard_get_char(void) {
    if (!keyboard_buffer_empty()) { // если буфер не пуст
        return keyboard_buffer_get(); // извлекаем символ из буфера
    }
    return 0; // возвращаем 0, если буфер пуст
}

// проверяет, есть ли данные в буфере
int keyboard_has_data(void) {
    return !keyboard_buffer_empty(); // возвращает true, если буфер не пуст
}

// проверяет, нажата ли клавиша Shift
unsigned char keyboard_is_shift_pressed(void) {
    return keyboard_state.shift_pressed; // возвращает true, если клавиша Shift нажата
}

// проверяет, нажата ли клавиша Ctrl
unsigned char keyboard_is_ctrl_pressed(void) {
    return keyboard_state.ctrl_pressed; // возвращает true, если клавиша Ctrl нажата
}

// проверяет, нажата ли клавиша Alt
unsigned char keyboard_is_alt_pressed(void) {
    return keyboard_state.alt_pressed; // возвращает true, если клавиша Alt нажата
}

// проверяет, нажата ли клавиша Caps Lock
unsigned char keyboard_is_caps_lock(void) {
    return keyboard_state.caps_lock; // возвращает true, если клавиша Caps Lock нажата
} 