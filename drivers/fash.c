// -----------------------------------------------
// KillerGrass OS (KGOS) Fash Driver
// -----------------------------------------------

// драйвер fash - управляет выводом текста в fash
// обеспечивает автоматический скроллинг и управление позицией курсора

#include "fash.h"
#include "vga.h"
#include "../kernel/logo.h"
#include "../libs/string.h"

// глобальные переменные fash
static int fash_y = FASH_START_Y;  // текущая позиция fash
static int fash_active = 1;  // Флаг активности Fash

// инициализация fash
// устанавливает начальную позицию и настройки
void fash_init(void) {
    fash_y = FASH_START_Y;
    fash_active = 1;
}

// функция для очистки строки на экране
// заполняет всю строку пробелами с правильным фоном
void fash_clear_line(int y) {
    for (int x = 0; x < VGA_WIDTH; x++) {
        vga_put_char_with_bg(x, y, ' ', VGA_WHITE, VGA_USE_GLOBAL_BG);
    }
}

// функция для вывода текста с правильным фоном
// использует установленный фон
void fash_print(int x, int y, const char* text, unsigned char color) {
    vga_print_text_with_bg(x, y, text, color, VGA_USE_GLOBAL_BG);
}

// функция для вывода текста в fash
// автоматически переводит курсор на следующую строку
void fash_output(const char* text, unsigned char color) {
    if (!fash_active) return;
    
    fash_print(0, fash_y, text, color);
    fash_y++;
    
    if (fash_y >= VGA_HEIGHT - 1) {
        vga_scroll_up();
        fash_y = VGA_HEIGHT - 2;
    }
}

// функция для вывода многострочного текста
// разбивает текст по символам новой строки
void fash_output_multiline(const char* text, unsigned char color) {
    char temp_buffer[256];
    int temp_pos = 0;
    
    while (*text) {
        if (*text == '\n') {
            temp_buffer[temp_pos] = '\0';
            if (temp_pos > 0) {
                fash_output(temp_buffer, color);
            } else {
                fash_output("", color); // пустая строка
            }
            temp_pos = 0;
        } else {
            temp_buffer[temp_pos++] = *text;
            if (temp_pos >= 255) {
                temp_buffer[temp_pos] = '\0';
                fash_output(temp_buffer, color);
                temp_pos = 0;
            }
        }
        text++;
    }
    
    // выводим оставшийся текст
    if (temp_pos > 0) {
        temp_buffer[temp_pos] = '\0';
        fash_output(temp_buffer, color);
    }
}

// функция для отображения промпта
// очищает строку и выводит приглашение к вводу
void fash_show_prompt(const char* prompt, int y, unsigned char color) {
    // очищаем строку промпта
    fash_clear_line(y);
    // выводим промпт
    fash_print(0, y, prompt, color);
}

// установка позиции fash
void fash_set_position(int y) {
    fash_y = y;
}

// получение текущей позиции fash
int fash_get_position(void) {
    return fash_y;
}

void fash_exit(void) {
    fash_active = 0;
    vga_clear_screen();
}

void fash_restart(void) {
    fash_init();
    vga_clear_screen();
    
    // перерисовываем интерфейс
    vga_set_background_color_and_clear(VGA_BLUE);
    logo_display();
    fash_show_prompt("fash> ", fash_get_position(), VGA_LIGHT_GREEN);
}