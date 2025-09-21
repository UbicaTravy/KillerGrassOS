// -----------------------------------------------
// KillerGrass OS (KGOS) Input Module
// -----------------------------------------------

// модуль управления вводом команд - обрабатывает буфер ввода и историю команд
// обеспечивает взаимодействие между клавиатурой и системой команд
// кстати он чёт не работает, ну и ладно)))

#include "input.h"
#include "commands/commands.h"

// глобальные переменные модуля ввода
static char input_buffer[INPUT_BUFFER_SIZE];
static int input_position = 0;
static command_history_t history = {0};

// инициализация модуля ввода
// устанавливает начальные значения буфера и истории
void input_init(void) {
    memset(input_buffer, 0, INPUT_BUFFER_SIZE);
    input_position = 0;
    history.count = 0;
    history.current = 0;
}

// обработка нажатия клавиши
// определяет тип клавиши и вызывает соответствующую функцию
void input_process_key(unsigned char scancode, char c) {
    if (c == '\n') {
        // Enter - обрабатываем команду
        input_process_command();
        
    } else if (scancode == KEY_BACKSPACE) {
        // Backspace - удаляем символ
        input_handle_backspace();
        
    } else if (c >= 32 && c <= 126) {
        // печатаемый символ - добавляем в буфер и выводим
        input_handle_printable_char(c);
    }
}

// обработка ввода команды
// добавляет команду в историю и выполняет её
void input_process_command(void) {
    if (input_position > 0) {
        // добавляем команду в историю
        if (history.count < MAX_HISTORY) {
            strcpy(history.commands[history.count], input_buffer);
            history.count++;
        } else {
            // сдвигаем историю если она переполнена
            for (int i = 0; i < MAX_HISTORY - 1; i++) {
                strcpy(history.commands[i], history.commands[i + 1]);
            }
            strcpy(history.commands[MAX_HISTORY - 1], input_buffer);
        }
        
        // выполняем команду
        execute_command(input_buffer);
        
        // очищаем буфер ввода
        input_clear_buffer();
    }
    
    // показываем новый промпт
    fash_show_prompt(PROMPT, fash_get_position(), VGA_LIGHT_GREEN);
}

// обработка backspace
// удаляет символ из буфера и с экрана
void input_handle_backspace(void) {
    if (input_position > 0) {
        input_position--;
        input_buffer[input_position] = '\0';
        
        // очищаем символ на экране
        int prompt_x = strlen(PROMPT);
        vga_put_char_with_bg(prompt_x + input_position, fash_get_position(), ' ', VGA_WHITE, VGA_USE_GLOBAL_BG);
    }
}

// обработка печатаемого символа
// добавляет символ в буфер и выводит на экран
void input_handle_printable_char(char c) {
    if (input_position < INPUT_BUFFER_SIZE - 1) {
        input_buffer[input_position] = c;
        input_position++;
        
        // выводим символ на экран
        int prompt_x = strlen(PROMPT);
        vga_put_char_with_bg(prompt_x + input_position - 1, fash_get_position(), c, VGA_WHITE, VGA_USE_GLOBAL_BG);
    }
}

// очистка буфера ввода
void input_clear_buffer(void) {
    memset(input_buffer, 0, INPUT_BUFFER_SIZE);
    input_position = 0;
}

// получение текущего буфера
char* input_get_buffer(void) {
    return input_buffer;
}

// получение текущей позиции
int input_get_position(void) {
    return input_position;
}