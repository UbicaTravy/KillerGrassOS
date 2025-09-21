#include "commands.h"
#include "../logo.h"

// команда info - показывает информацию об ОС
// выводит логотип и информацию о версии
int cmd_info(const char* args) {
    (void)args; // игнорируем аргументы
    
    // выводим пустую строку чтобы не перекрыть промпт
    fash_output("", VGA_WHITE);
    
    print_logo_cmd();
    fash_output("KillerGrass OS v0.0003", VGA_WHITE);
    fash_output("Created by KillerGrass, 2025", VGA_LIGHT_BLUE);
    fash_output("Made in Russia in Siberia", VGA_RED);
    
    return 0;
}