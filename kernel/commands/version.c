#include "commands.h"

// команда version - показывает версию ОС
// простая команда для отображения версии
int cmd_version(const char* args) {
    (void)args; // игнорируем аргументы
    
    // выводим пустую строку чтобы не перекрыть промпт
    fash_output("", VGA_WHITE);
    
    fash_output("KGOS v0.0003", VGA_LIGHT_GREEN);
    fash_output("Kernel version: 1.0", VGA_WHITE);
    fash_output("Build date: 2025", VGA_LIGHT_CYAN);
    
    return 0;
} 