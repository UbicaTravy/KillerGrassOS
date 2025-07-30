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

// FecalOS VGA Driver
// Author: KillerGrass

#ifndef VGA_H
#define VGA_H

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
#define VGA_LIGHT_YELLOW  0x0E  // тот же цвет, что и LIGHT_BROWN
#define VGA_WHITE         0x0F

// константы VGA
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_BUFFER 0xB8000

// специальные значения для цвета фона
#define VGA_USE_GLOBAL_BG 0xFF  // использовать глобальный цвет фона

// функции драйвера VGA
void vga_init(void); // инициализация VGA драйвера
void vga_clear_screen(void); // очистка экрана
void vga_set_color(unsigned char color); // установка цвета
unsigned char vga_get_color(void); // получение текущего цвета
void vga_put_char(int x, int y, char c, unsigned char color); // вывод символа
void vga_put_char_with_bg(int x, int y, char c, unsigned char text_color, unsigned char bg_color); // вывод символа с фоном
void vga_print_text(int x, int y, const char *text, unsigned char color); // вывод текста
void vga_print_text_with_bg(int x, int y, const char *text, unsigned char text_color, unsigned char bg_color); // вывод текста с фоном
void vga_print_centered(int y, const char *text, unsigned char color); // вывод текста по центру
void vga_print_centered_with_bg(int y, const char *text, unsigned char text_color, unsigned char bg_color); // вывод текста по центру с фоном
void vga_scroll_up(void); // скроллинг экрана
void vga_set_cursor(int x, int y); // установка курсора
void vga_set_background_color(unsigned char bg_color); // установка цвета фона
void vga_set_background_color_and_clear(unsigned char bg_color); // установка цвета фона и очистка экрана

#endif 