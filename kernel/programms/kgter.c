#include "runner.h"
#include "api.h"

// простой текстовый редактор с прокруткой по стрелкам вверх/вниз
// управление: ввод текста, Backspace, Enter; ESC или Ctrl+X — выход

#define KGTER_MAX_LINES   200
#define KGTER_MAX_COLS    80

static char buffer[KGTER_MAX_LINES][KGTER_MAX_COLS + 1];
static int line_count = 1;
static int cursor_line = 0;
static int cursor_col = 0;
static int scroll_top = 0;

static void kgter_draw(void) {
    program_draw_header("KillerGrass Text Editor (KGTER)", "ESC or CTRL+X to exit | Arrows Up/Down to scroll");

    int visible_rows = VGA_HEIGHT - 3;
    for (int i = 0; i < visible_rows; i++) {
        int src = scroll_top + i;
        if (src >= line_count) break;
        vga_print_text(0, 2 + i, buffer[src], VGA_WHITE);
    }

    int cursor_y = 2 + (cursor_line - scroll_top);
    if (cursor_y >= 2 && cursor_y < 2 + visible_rows) {
        vga_set_cursor(cursor_col, cursor_y);
    } else {
        vga_set_cursor(0, 0);
    }
}

static void kgter_insert_char(char c) {
    if (c == '\n') {
        // finish current line and move to next line, creating it if needed
        if (cursor_line < KGTER_MAX_LINES - 1) {
            cursor_line++;
            if (cursor_line >= line_count) {
                line_count = cursor_line + 1;
                buffer[cursor_line][0] = '\0';
            }
            cursor_col = 0;
            // autoscroll when caret goes beyond view
            int visible_rows = VGA_HEIGHT - 3;
            if (cursor_line >= scroll_top + visible_rows) {
                scroll_top = cursor_line - visible_rows + 1;
            }
        }
        return;
    }

    // Автоматический перенос на новую строку при заполнении текущей
    if (cursor_col >= KGTER_MAX_COLS) {
        if (cursor_line < KGTER_MAX_LINES - 1) {
            cursor_line++;
            if (cursor_line >= line_count) {
                line_count = cursor_line + 1;
                buffer[cursor_line][0] = '\0';
            }
            cursor_col = 0;
            
            // автопрокрутка если курсор ушел ниже экрана
            int visible_rows = VGA_HEIGHT - 3;
            if (cursor_line >= scroll_top + visible_rows) {
                scroll_top = cursor_line - visible_rows + 1;
            }
        } else {
            // Достигнут максимум строк, не можем добавить больше
            return;
        }
    }

    if (cursor_col < KGTER_MAX_COLS) {
        buffer[cursor_line][cursor_col] = c;
        cursor_col++;
        buffer[cursor_line][cursor_col] = '\0';
    }
}

static void kgter_backspace(void) {
    if (cursor_col > 0) {
        cursor_col--;
        buffer[cursor_line][cursor_col] = '\0';
    } else if (cursor_line > 0) {
        cursor_line--;
        // переместим курсор в конец предыдущей строки
        int len = 0;
        while (buffer[cursor_line][len] && len < KGTER_MAX_COLS) len++;
        cursor_col = len;
    }
}

static void kgter_scroll_up(void) {
    if (scroll_top > 0) {
        scroll_top--;
    }
}

static void kgter_scroll_down(void) {
    int visible_rows = VGA_HEIGHT - 3;
    if (scroll_top + visible_rows < line_count) {
        scroll_top++;
    }
}

void prog_kgter(void) {
    for (int i = 0; i < KGTER_MAX_LINES; i++) {
        buffer[i][0] = '\0';
    }
    line_count = 1;
    cursor_line = 0;
    cursor_col = 0;
    scroll_top = 0;

    kgter_draw();

    while (1) {
        unsigned char sc = keyboard_read_scancode();
        if (!sc) continue;

        if (program_should_exit(sc)) break;

        if (sc == KEY_BACKSPACE) {
            kgter_backspace();
            kgter_draw();
            continue;
        }

        // обработка стрелок: extended префикс 0xE0, следующий код — направление
        if (sc == KEY_EXTENDED) {
            unsigned char next = keyboard_read_scancode();
            if (!next) continue;
            if (next == KEY_UP) {
                kgter_scroll_up();
                kgter_draw();
                continue;
            } else if (next == KEY_DOWN) {
                kgter_scroll_down();
                kgter_draw();
                continue;
            }
            continue;
        }

        char ch = keyboard_scancode_to_ascii(sc);
        if (ch) {
            kgter_insert_char(ch);
            // автопрокрутка если курсор ушел ниже экрана
            int visible_rows = VGA_HEIGHT - 3;
            if (cursor_line >= scroll_top + visible_rows) {
                scroll_top = cursor_line - visible_rows + 1;
            }
            kgter_draw();
        }
    }
}


