// заголовочный файл для драйвера fash (fash.c)
// содержит функции для работы с fash - вывод текста, управление курсором, скроллинг

// KillerGrass OS (KGOS) Fash Driver
// Author: KillerGrass

#ifndef FASH_H
#define FASH_H

#include "vga.h"
#include "../libs/types.h"

// константы fash
#define FASH_START_Y 15
#define INPUT_BUFFER_SIZE 256

// функции драйвера fash
void fash_init(void);
void fash_clear_line(int y);
void fash_print(int x, int y, const char* text, unsigned char color);
void fash_output(const char* text, unsigned char color);
void fash_output_multiline(const char* text, unsigned char color);
void fash_show_prompt(const char* prompt, int y, unsigned char color);
void fash_set_position(int y);
int fash_get_position(void);
void fash_exit(void);
void fash_restart(void);

#endif