// тут я пытался сделать свой API для программ, но обдрищился и забил

#ifndef PROGRAM_API_H
#define PROGRAM_API_H

#include "runner.h"

// рисуем стандартный заголовок с заголовком и линиями подсказки в строках 0 и 1
static inline void program_draw_header(const char* title, const char* hint) {
    vga_clear_screen();
    vga_print_centered(0, title, VGA_LIGHT_CYAN);
    if (hint && hint[0]) {
        vga_print_centered(1, hint, VGA_LIGHT_GREY);
    }
}

// возвращает ненулевое значение, если программа должна завершить работу на основе скан-кода (ESC или Ctrl+X)
static inline int program_should_exit(unsigned char scancode) {
    if (scancode == KEY_ESC) return 1;
    if ((scancode == KEY_X) && keyboard_is_ctrl_pressed()) return 1;
    return 0;
}

#endif


