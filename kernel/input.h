// заголовочный файл для модуля управления вводом команд (input.c)
// содержит функции для работы с буфером ввода, историей команд и обработкой клавиатуры

// KillerGrass OS (KGOS) Input Module
// Author: KillerGrass

#ifndef INPUT_H
#define INPUT_H

#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../drivers/fash.h"
#include "../libs/types.h"
#include "../libs/string.h"

// константы для ввода
#define INPUT_BUFFER_SIZE 256
#define PROMPT "fash> "
#define MAX_HISTORY 10      // максимальное количество команд в истории

// структура для хранения истории команд
// позволяет пользователю использовать стрелки для навигации
typedef struct {
    char commands[MAX_HISTORY][INPUT_BUFFER_SIZE];
    int count;
    int current;
} command_history_t;

void input_init(void);
void input_process_key(unsigned char scancode, char c);
void input_process_command(void);
void input_handle_backspace(void);
void input_handle_printable_char(char c);
void input_clear_buffer(void);
char* input_get_buffer(void);
int input_get_position(void);

#endif