#ifndef COMMANDS_H
#define COMMANDS_H

#include "../../drivers/vga.h"
#include "../../drivers/keyboard.h"
#include "../../drivers/fash.h"
#include "../../drivers/io.h"
#include "../../libs/types.h"
#include "../../libs/string.h"

// структура команды - содержит имя, описание и функцию выполнения
typedef struct {
    const char* name;
    const char* description;
    int (*execute)(const char* args);
} command_t;

// функции для работы с системой команд
void commands_init(void);
int execute_command(const char* input);
void register_command(const char* name, const char* description, int (*execute)(const char* args));

// объявления функций команд
int cmd_help(const char* args);
int cmd_clear(const char* args);
int cmd_echo(const char* args);
int cmd_info(const char* args);
int cmd_version(const char* args);
int cmd_date(const char* args);
int cmd_memory(const char* args);
int cmd_reboot(const char* args);
int cmd_exit(const char* args);
int cmd_color(const char* args);
int cmd_run(const char* args);
int cmd_demo(const char* args);
int cmd_kg(const char* args);

// вспомогательные функции
void print_logo_cmd(void);

#endif