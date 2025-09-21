// заголовочный файл для модуля отображения логотипа (logo.c)
// содержит функции для отображения логотипа и информации о системе

// KillerGrass OS (KGOS) Logo Module
// Author: KillerGrass

#ifndef LOGO_H
#define LOGO_H

#include "../drivers/vga.h"

// функции модуля логотипа
void logo_display(void); // отображение логотипа и информации о системе
void logo_print_ascii_art(void); // отображение ASCII-арт логотипа
void print_logo_cmd(void); // вывод логотипа в командах

#endif 