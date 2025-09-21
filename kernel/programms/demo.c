// ну самая простецкая программа для показа чё могёт моя ОС

#include "runner.h"

void prog_demo(void) {
    vga_clear_screen();
    vga_print_centered(0, "DEMO PROGRAM", VGA_LIGHT_CYAN);
    vga_print_centered(2, "Press ESC or CTRL+X to exit", VGA_WHITE);
    while (1) {
        unsigned char sc = keyboard_read_scancode();
        if (sc) {
            if (sc == KEY_ESC) break;
            if ((sc == KEY_X) && keyboard_is_ctrl_pressed()) break;
        }
    }
}


