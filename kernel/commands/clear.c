#include "commands.h"

// команда clear - очищает экран
// использует vga_set_background_color_and_clear для полной очистки
int cmd_clear(const char* args) {
    (void)args; // игнорируем аргументы
    
    // выводим пустую строку чтобы не перекрыть промпт
    fash_output("", VGA_USE_GLOBAL_BG);
    
    vga_clear_screen();
    return 0;
} 