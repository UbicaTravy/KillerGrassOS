#include "commands.h"

// команда memory - показывает информацию о памяти системы
// в реальной ОС здесь будет чтение из BIOS memory map
int cmd_memory(const char* args) {
    (void)args; // игнорируем аргументы
    
    // выводим пустую строку чтобы не перекрыть промпт
    fash_output("", VGA_WHITE);
    
    fash_output("Memory Information:", VGA_LIGHT_GREEN);
    fash_output("Total RAM: 512 MB", VGA_WHITE);
    fash_output("Available RAM: 480 MB", VGA_WHITE);
    fash_output("Kernel size: ~13 KB", VGA_LIGHT_CYAN);
    fash_output("Memory layout:", VGA_LIGHT_GREEN);
    fash_output("  0x00000000 - 0x0009FFFF: Lower Memory (640 KB)", VGA_WHITE);
    fash_output("  0x000A0000 - 0x000BFFFF: Video Memory (128 KB)", VGA_WHITE);
    fash_output("  0x000C0000 - 0x000FFFFF: ROM Area (256 KB)", VGA_WHITE);
    fash_output("  0x00100000 - 0x1FFFFFFF: Extended Memory", VGA_WHITE);
    
    return 0;
} 