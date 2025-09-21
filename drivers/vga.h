// Заголовочный файл для VGA драйвера (vga.c)
// Здесь хранятся все константы и структуры для работы с VGA

// Реализация VGA драйвера:
// - Инициализация VGA драйвера через функцию vga_init через функцию vga_clear_screen и глобальные переменные cursor_x и cursor_y и текущий цвет current_color через цикл и проверкой на границы экрана
// - Очистка экрана через функцию vga_clear_screen методом заполнения буфера пробелами и текущим цветом через цикл и глобальную переменную current_color через цикл и проверкой на границы экрана
// - Установка цвета через функцию vga_set_color методом установки текущего цвета через глобальную переменную current_color через цикл и проверкой на границы экрана
// - Вывод символа через функцию vga_put_char методом записи символа и цвета в буфер с проверкой на границы экрана через цикл и проверкой на границы экрана
// - Вывод текста через функцию vga_print_text методом вывода символов и цвета в буфер с переносом строки и выравниванием по табуляции через цикл и проверкой на границы экрана
// - Вывод текста по центру через функцию vga_print_centered методом вывода символов и цвета в буфер с выравниванием по центру через цикл и проверкой на границы экрана 
// - Скроллинг экрана через функцию vga_scroll_up методом копирования строк вверх и очистки последней строки с текущим цветом через цикл и проверкой на границы экрана
// - Установка курсора через функцию vga_set_cursor методом сохранения позиции курсора через глобальные переменные cursor_x и cursor_y и проверкой на границы экрана

// Функции для работы с буфером:
// - vga_put_char - вывод символа в буфер
// - vga_print_text - вывод текста в буфер
// - vga_print_centered - вывод текста по центру в буфер
// - vga_scroll_up - скроллинг экрана
// - vga_set_cursor - установка курсора

// KillerGrass OS (KGOS) VGA Driver
// Author: KillerGrass

// vga.h
#ifndef VGA_H
#define VGA_H

#include "../libs/types.h"

// цвета VGA
#define VGA_BLACK         0x00
#define VGA_BLUE          0x01
#define VGA_GREEN         0x02
#define VGA_CYAN          0x03
#define VGA_RED           0x04
#define VGA_MAGENTA       0x05
#define VGA_BROWN         0x06
#define VGA_LIGHT_GREY    0x07
#define VGA_DARK_GREY     0x08
#define VGA_LIGHT_BLUE    0x09
#define VGA_LIGHT_GREEN   0x0A
#define VGA_LIGHT_CYAN    0x0B
#define VGA_LIGHT_RED     0x0C
#define VGA_LIGHT_MAGENTA 0x0D
#define VGA_LIGHT_BROWN   0x0E
#define VGA_LIGHT_YELLOW  0x0E
#define VGA_WHITE         0x0F

// константы VGA для стандартного текстового режима 80x25
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_BUFFER 0xB8000

// специальные значения
#define VGA_USE_GLOBAL_BG 0xFF

// функции для работы с VGA регистрами
void vga_write_reg(uint8_t reg, uint8_t value);
uint8_t vga_read_reg(uint8_t reg);
// больше не используем кастомный режим 120x80
// void vga_set_mode_120x80(void);

// основные функции драйвера
void vga_init(void);
void vga_clear_screen(void);
void vga_set_color(unsigned char color);
unsigned char vga_get_color(void);
void vga_put_char(int x, int y, char c, unsigned char color);
void vga_put_char_with_bg(int x, int y, char c, unsigned char text_color, unsigned char bg_color);
void vga_print_text(int x, int y, const char *text, unsigned char color);
void vga_print_text_with_bg(int x, int y, const char *text, unsigned char text_color, unsigned char bg_color);
void vga_print_centered(int y, const char *text, unsigned char color);
void vga_print_centered_with_bg(int y, const char *text, unsigned char text_color, unsigned char bg_color);
void vga_scroll_up(void);
void vga_set_cursor(int x, int y);
void vga_set_background_color(unsigned char bg_color);
void vga_set_background_color_and_clear(unsigned char bg_color);
void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void vga_disable_cursor(void);

#endif