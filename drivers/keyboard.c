// KillerGrass OS (KGOS) Keyboard Driver - Simple Implementation
// Author: KillerGrass

#include "keyboard.h"
#include "../libs/types.h"
#include "../libs/string.h"

// глобальное состояние клавиатуры
keyboard_state_t keyboard_state = {0};

// простые функции для работы с портами
static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

// инициализация клавиатуры
void keyboard_init(void) {
    memset(&keyboard_state, 0, sizeof(keyboard_state_t));
    
    // очищаем буфер клавиатуры
    while (inb(PS2_COMMAND_PORT) & 0x01) {
        inb(PS2_DATA_PORT);
    }
}

// чтение скан-кода
unsigned char keyboard_read_scancode(void) {
    if (inb(PS2_COMMAND_PORT) & 0x01) {
        unsigned char scancode = inb(PS2_DATA_PORT);
        
        // обработка модификаторов
        if (scancode == KEY_CTRL) {
            keyboard_state.ctrl_pressed = 1;
        } else if (scancode == (KEY_CTRL | KEY_RELEASE)) {
            keyboard_state.ctrl_pressed = 0;
        } else if (scancode == KEY_LSHIFT || scancode == KEY_RSHIFT) {
            keyboard_state.shift_pressed = 1;
        } else if (scancode == (KEY_LSHIFT | KEY_RELEASE) || scancode == (KEY_RSHIFT | KEY_RELEASE)) {
            keyboard_state.shift_pressed = 0;
        }
        
        // обработка обычных клавиш
        if (!(scancode & KEY_RELEASE)) {
            keyboard_buffer_put(scancode);
        }
        
        return scancode;
    }
    return 0;
}

// преобразование скан-кода в ASCII
char keyboard_scancode_to_ascii(unsigned char scancode) {
    // проверяем, что это не отпускание клавиши
    if (scancode & KEY_RELEASE) {
        return 0;
    }
    
    // простая таблица преобразования
    static const char scancode_table[] = {
        0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
        0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
        'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0
    };
    
    // таблица символов с Shift для цифрового ряда и специальных символов
    static const char shift_scancode_table[] = {
        0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0,
        0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|',
        'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0
    };
    
    if (scancode < sizeof(scancode_table)) {
        char c;
        
        // если Shift зажат, используем таблицу с Shift
        if (keyboard_state.shift_pressed) {
            c = shift_scancode_table[scancode];
            
            // для букв также учитываем Caps Lock
            if (keyboard_state.caps_lock && c >= 'A' && c <= 'Z') {
                c += 32; // Преобразуем в нижний регистр
            }
            else if (keyboard_state.caps_lock && c >= 'a' && c <= 'z') {
                c -= 32; // преобразуем в верхний регистр
            }
        } else {
            c = scancode_table[scancode];
            
            // обработка Caps Lock для букв
            if (keyboard_state.caps_lock && c >= 'a' && c <= 'z') {
                c -= 32; // преобразуем в верхний регистр
            }
            else if (keyboard_state.caps_lock && c >= 'A' && c <= 'Z') {
                c += 32; // преобразуем в нижний регистр
            }
        }
        
        return c;
    }
    return 0;
}

// получение символа
char keyboard_get_char(void) {
    if (!keyboard_buffer_empty()) {
        unsigned char scancode = keyboard_buffer_get();
        return keyboard_scancode_to_ascii(scancode);
    }
    return 0;
}

// проверка наличия данных
int keyboard_has_data(void) {
    return !keyboard_buffer_empty();
}

// обработка ввода
void keyboard_handle_input(void) {
    unsigned char scancode = keyboard_read_scancode();
    if (scancode != 0) {
        // обрабатываем скан-код (пока без использования результата, чтобы не ловить warning)
        (void)keyboard_scancode_to_ascii(scancode);
    }
}

// функции для работы с буфером
void keyboard_buffer_put(unsigned char c) {
    if (keyboard_state.count < KEYBOARD_BUFFER_SIZE) {
        keyboard_state.buffer[keyboard_state.tail] = c;
        keyboard_state.tail = (keyboard_state.tail + 1) % KEYBOARD_BUFFER_SIZE;
        keyboard_state.count++;
    }
}

unsigned char keyboard_buffer_get(void) {
    if (keyboard_state.count > 0) {
        unsigned char c = keyboard_state.buffer[keyboard_state.head];
        keyboard_state.head = (keyboard_state.head + 1) % KEYBOARD_BUFFER_SIZE;
        keyboard_state.count--;
        return c;
    }
    return 0;
}

int keyboard_buffer_empty(void) {
    return keyboard_state.count == 0; // не ну ачё))
}

// функции для работы с модификаторами
unsigned char keyboard_is_shift_pressed(void) {
    return keyboard_state.shift_pressed;
}

unsigned char keyboard_is_ctrl_pressed(void) {
    return keyboard_state.ctrl_pressed;
}

unsigned char keyboard_is_alt_pressed(void) {
    return keyboard_state.alt_pressed;
}

unsigned char keyboard_is_caps_lock(void) {
    return keyboard_state.caps_lock;
}