// Заголовочный файл для клавиатуры (keyboard.c)
// Здесь хранятся все константы и структуры для работы с клавиатурой

// Здесь есть:
// - PS/2 порты клавиатуры
// - Скан-коды клавиш
// - Специальные коды
// - Размер буфера клавиатуры
// - Структура для хранения состояния клавиатуры
// - Функции драйвера
// - Функции для работы с буфером
// - Функции для работы с модификаторами

// KillerGrass OS (KGOS) Keyboard Driver
// Author: KillerGrass

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "vga.h"

// PS/2 порты
#define PS2_DATA_PORT    0x60
#define PS2_COMMAND_PORT 0x64

// коды клавиш
#define KEY_ESC          0x01
#define KEY_ENTER        0x1C
#define KEY_BACKSPACE    0x0E
#define KEY_TAB          0x0F
#define KEY_LSHIFT       0x2A
#define KEY_RSHIFT       0x36
#define KEY_CTRL         0x1D
#define KEY_ALT          0x38
#define KEY_CAPS_LOCK    0x3A
#define KEY_F1           0x3B
#define KEY_F2           0x3C
#define KEY_F3           0x3D
#define KEY_F4           0x3E
#define KEY_F5           0x3F
#define KEY_F6           0x40
#define KEY_F7           0x41
#define KEY_F8           0x42
#define KEY_F9           0x43
#define KEY_F10          0x44
#define KEY_F11          0x57
#define KEY_F12          0x58
#define KEY_X            0x2D

// стрелочные клавиши (используются после префикса 0xE0)
#define KEY_UP           0x48
#define KEY_LEFT         0x4B
#define KEY_RIGHT        0x4D
#define KEY_DOWN         0x50

// специальные коды
#define KEY_RELEASE      0x80
#define KEY_EXTENDED     0xE0

// размер буфера
#define KEYBOARD_BUFFER_SIZE 256

// структура для хранения состояния клавиатуры
typedef struct {
    unsigned char buffer[KEYBOARD_BUFFER_SIZE];
    int head;
    int tail;
    int count;
    unsigned char shift_pressed;
    unsigned char ctrl_pressed;
    unsigned char alt_pressed;
    unsigned char caps_lock;
} keyboard_state_t;

// функции драйвера
void keyboard_init(void);
unsigned char keyboard_read_scancode(void);
char keyboard_scancode_to_ascii(unsigned char scancode);
char keyboard_get_char(void);
int keyboard_has_data(void);
void keyboard_handle_input(void);

// функции для работы с буфером
void keyboard_buffer_put(unsigned char c);
unsigned char keyboard_buffer_get(void);
int keyboard_buffer_empty(void);

// функции для работы с модификаторами
unsigned char keyboard_is_shift_pressed(void);
unsigned char keyboard_is_ctrl_pressed(void);
unsigned char keyboard_is_alt_pressed(void);
unsigned char keyboard_is_caps_lock(void);

// Глобальное состояние клавиатуры
extern keyboard_state_t keyboard_state;

#endif