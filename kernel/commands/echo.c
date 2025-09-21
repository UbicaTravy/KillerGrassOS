#include "commands.h"

// команда echo - выводит переданный текст
// если аргументы есть - выводит их, иначе ничего не делает
int cmd_echo(const char* args) {
    // выводим пустую строку чтобы не перекрыть промпт
    fash_output("", VGA_WHITE);
    
    if (args && strlen(args) > 0) {
        fash_output(args, VGA_WHITE);
    }
    return 0;
} 