#include "commands.h"

// команда help - показывает список доступных команд
// нужна пустая строка перед выводом чтобы не перекрыть промпт
int cmd_help(const char* args) {
    (void)args; // игнорируем аргументы
    
    // выводим пустую строку чтобы не перекрыть промпт
    fash_output("", VGA_WHITE);
    
    fash_output("Available commands:", VGA_LIGHT_GREEN);
    fash_output("help - show all commands", VGA_WHITE);
    fash_output("clear - clear screen", VGA_WHITE);
    fash_output("echo - print text", VGA_WHITE);
    fash_output("info - show info about OS", VGA_WHITE);
    fash_output("version - show OS version", VGA_WHITE);
    fash_output("date - show current date and time", VGA_WHITE);
    fash_output("memory - show memory information", VGA_WHITE);
    fash_output("reboot - reboot the system", VGA_WHITE);
    fash_output("color - change background color", VGA_WHITE);
    fash_output("exit - exit from KillerGrass OS", VGA_WHITE);
    fash_output("run - run program by name", VGA_WHITE);
    fash_output("demo - run demo program", VGA_WHITE);
    fash_output("kg - run KillerGrass Text Editor (KGTER)", VGA_WHITE);
    
    fash_output("", VGA_WHITE);
    
    return 0;
} 