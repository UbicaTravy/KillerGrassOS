// -----------------------------------------------
// FecalOS VGA Driver — краткое описание и справка
// -----------------------------------------------

// Подключение:
// VGA работает через порт 0x3D4. Буфер кадров (framebuffer) расположен по адресу 0xB8000.

// Основные возможности драйвера:
// 1. Инициализация: vga_init()
// 2. Очистка экрана: vga_clear_screen() — заполняет буфер пробелами и текущим цветом (current_color)
// 3. Установка цвета: vga_set_color() — меняет текущий цвет текста/фона
// 4. Вывод символа: vga_put_char() — записывает символ и цвет в буфер с проверкой границ
// 5. Вывод строки: vga_print_text() — печатает текст с поддержкой переноса и табуляции
// 6. Центрирование: vga_print_centered() — выводит строку по центру заданной строки
// 7. Скроллинг: vga_scroll_up() — сдвигает содержимое вверх, очищает последнюю строку
// 8. Курсор: vga_set_cursor() — задаёт позицию курсора (cursor_x, cursor_y)

// Быстрые подсказки по использованию:
// - vga_put_char(x, y, ch, color)         // символ в буфер
// - vga_print_text(x, y, "text", color)   // строка в буфер
// - vga_print_centered(y, "text", color)  // строка по центру
// - vga_scroll_up()                       // скроллинг
// - vga_set_cursor(x, y)                  // позиция курсора

// Справка для новичков:

// Кадровый буфер (framebuffer) — область памяти, где формируется изображение для экрана.
// В текстовом режиме VGA: 80 столбцов × 25 строк, каждый символ — 2 байта (символ + цвет).
// Адрес: 0xB8000. Размер: 4000 байт.

// Пример обращения к буферу:
//   volatile char *vga = (volatile char*)(uintptr_t)VGA_BUFFER;
//   vga[i] = 'A';         // символ
//   vga[i+1] = color;     // цвет

// Изменить размеры экрана можно в vga.h:
//   #define VGA_WIDTH 100
//   #define VGA_HEIGHT 30

// Примеры вызова функций:
//   vga_clear_screen();                        // очистить экран
//   vga_set_color(VGA_LIGHT_GREY);             // установить цвет
//   vga_put_char(0, 0, 'A', VGA_LIGHT_GREY);   // символ
//   vga_print_text(0, 0, "Hello!", VGA_LIGHT_GREY); // строка
//   vga_print_centered(0, "Hello!", VGA_LIGHT_GREY); // по центру
//   vga_scroll_up();                           // скроллинг
//   vga_set_cursor(0, 0);                      // курсор

// О VGA:
// VGA — классический видеоадаптер: 16 цветов, 80×25 символов. Просто и быстро.
// Есть и другие стандарты (например, VESA: 256 цветов, 800×600), но для простых ОС VGA — оптимальный выбор.

// Почему не BIOS-прерывания?
// Для экрана — слишком медленно. Для клавиатуры и дисков — можно использовать, но здесь всё делается напрямую.

// Этот драйвер — простое и эффективное решение для текстового режима. Если нужно больше — расширяйте под себя!

// Автор: KillerGrass

#include "vga.h" // включаем заголовочный файл для VGA драйвера
#include "../types.h" // собственные типы для standalone ОС

// глобальные переменные для позиции курсора
static int cursor_x = 0; // позиция курсора по X
static int cursor_y = 0; // позиция курсора по Y
static unsigned char current_color = VGA_LIGHT_GREY; // текущий цвет

// инициализация VGA драйвера
void vga_init(void) {
    vga_clear_screen(); // очищаем экран
    cursor_x = 0; // устанавливаем позицию курсора по X
    cursor_y = 0; // устанавливаем позицию курсора по Y
    current_color = VGA_LIGHT_GREY; // устанавливаем текущий цвет
}

// очистка экрана
void vga_clear_screen(void) {
    volatile char *vga = (volatile char*)(uintptr_t)VGA_BUFFER;
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i += 2) {
        vga[i] = ' '; // заполняем буфер пробелами
        vga[i+1] = current_color; // устанавливаем текущий цвет
    }
    cursor_x = 0; // устанавливаем позицию курсора по X
    cursor_y = 0; // устанавливаем позицию курсора по Y
}

// установка цвета
void vga_set_color(unsigned char color) {
    current_color = color; // устанавливаем текущий цвет
}

// получение текущего цвета
unsigned char vga_get_color(void) {
    return current_color; // возвращаем текущий цвет
}

// изменить цвет фона
void vga_set_background_color(unsigned char bg_color) {
    vga_set_color((vga_get_color() & 0x0F) | (bg_color << 4));
}

// изменить цвет фона и очистить экран
void vga_set_background_color_and_clear(unsigned char bg_color) {
    vga_set_background_color(bg_color);
    vga_clear_screen();
}

// вывод символа в буфер
void vga_put_char(int x, int y, char c, unsigned char color) {
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT) {
        volatile char *vga = (volatile char*)(uintptr_t)VGA_BUFFER;
        int offset = y * VGA_WIDTH * 2 + x * 2;
        vga[offset] = c;
        vga[offset + 1] = color;
    }
}

// вывод символа с индивидуальным цветом фона
void vga_put_char_with_bg(int x, int y, char c, unsigned char text_color, unsigned char bg_color) {
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT) {
        volatile char *vga = (volatile char*)(uintptr_t)VGA_BUFFER;
        int offset = y * VGA_WIDTH * 2 + x * 2;
        vga[offset] = c;
        
        // Если bg_color == VGA_USE_GLOBAL_BG, используем глобальный фон
        if (bg_color == VGA_USE_GLOBAL_BG) {
            vga[offset + 1] = (current_color & 0xF0) | (text_color & 0x0F);
        } else {
            vga[offset + 1] = (bg_color << 4) | (text_color & 0x0F);
        }
    }
}

// вывод текста в буфер
void vga_print_text(int x, int y, const char *text, unsigned char color) {
    int pos_x = x;
    while (*text) {
        if (*text == '\n') {
            pos_x = x;
            y++;
        } else if (*text == '\t') {
            pos_x = (pos_x + 8) & ~7; // выравнивание по табуляции
        } else {
            if (y >= VGA_HEIGHT) {
                vga_scroll_up();
                y = VGA_HEIGHT - 1;
            }
            vga_put_char(pos_x, y, *text, color);
            pos_x++;
        }
        text++;
        if (pos_x >= VGA_WIDTH) {
            pos_x = 0;
            y++;
        }
    }
}

// вывод текста с индивидуальным цветом фона
void vga_print_text_with_bg(int x, int y, const char *text, unsigned char text_color, unsigned char bg_color) {
    int pos_x = x;
    while (*text) {
        if (*text == '\n') {
            pos_x = x;
            y++;
        } else if (*text == '\t') {
            pos_x = (pos_x + 8) & ~7; // выравнивание по табуляции
        } else {
            if (y >= VGA_HEIGHT) {
                vga_scroll_up();
                y = VGA_HEIGHT - 1;
            }
            vga_put_char_with_bg(pos_x, y, *text, text_color, bg_color);
            pos_x++;
        }
        text++;
        if (pos_x >= VGA_WIDTH) {
            pos_x = 0;
            y++;
        }
    }
}

// вывод текста по центру в буфер
void vga_print_centered(int y, const char *text, unsigned char color) {
    int len = 0;
    const char *temp = text;
    while (*temp++) len++;
    int x = (VGA_WIDTH - len) / 2;
    if (x < 0) x = 0;
    vga_print_text(x, y, text, color);
}

// вывод текста по центру с индивидуальным цветом фона
void vga_print_centered_with_bg(int y, const char *text, unsigned char text_color, unsigned char bg_color) {
    int len = 0;
    const char *temp = text;
    while (*temp++) len++;
    int x = (VGA_WIDTH - len) / 2;
    if (x < 0) x = 0;
    vga_print_text_with_bg(x, y, text, text_color, bg_color);
}

// скроллинг экрана
void vga_scroll_up(void) {
    volatile char *vga = (volatile char*)(uintptr_t)VGA_BUFFER;
    
    // Копируем строки вверх
    for (int y = 0; y < VGA_HEIGHT - 1; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            int src_offset = (y + 1) * VGA_WIDTH * 2 + x * 2;
            int dst_offset = y * VGA_WIDTH * 2 + x * 2;
            vga[dst_offset] = vga[src_offset];
            vga[dst_offset + 1] = vga[src_offset + 1];
        }
    }
    
    // очищаем последнюю строку
    for (int x = 0; x < VGA_WIDTH; x++) {
        int offset = (VGA_HEIGHT - 1) * VGA_WIDTH * 2 + x * 2;
        vga[offset] = ' '; // заполняем буфер пробелами
        vga[offset + 1] = current_color; // устанавливаем текущий цвет
    }
}

// установка курсора
void vga_set_cursor(int x, int y) {
    cursor_x = x; // устанавливаем позицию курсора по X
    cursor_y = y; // устанавливаем позицию курсора по Y
    
    // просто сохраняем позицию курсора
    // аппаратный курсор можно будет добавить позже
} 