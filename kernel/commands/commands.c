#include "commands.h"

#define MAX_COMMANDS 16

// массив для хранения зарегистрированных команд
static command_t commands[MAX_COMMANDS];
static int command_count = 0;

// инициализация системы команд
// регистрирует все доступные команды в системе
void commands_init(void) {
    command_count = 0;
    
    // регистрируем все команды
    // так сделано потому что не знаю как автоматизировать
    // да и вам не составит труда ручками поработать
    register_command("help", "Show available commands", cmd_help);
    register_command("clear", "Clear the screen", cmd_clear);
    register_command("echo", "Print text", cmd_echo);
    register_command("info", "Show OS information", cmd_info);
    register_command("version", "Show OS version", cmd_version);
    register_command("date", "Show current date and time", cmd_date);
    register_command("memory", "Show memory information", cmd_memory);
    register_command("reboot", "Reboot the system", cmd_reboot);
    register_command("color", "Change background color", cmd_color);
    register_command("exit", "Exit the system", cmd_exit);
    register_command("run", "Run program from kernel/programms/<name>", cmd_run);
    register_command("demo", "Run demo program", cmd_demo);
    register_command("kg", "Run KillerGrass Text Editor", cmd_kg);
}

// регистрация новой команды в системе
// добавляет команду в массив если есть место
void register_command(const char* name, const char* description, int (*execute)(const char* args)) {
    if (command_count < MAX_COMMANDS) {
        commands[command_count].name = name;
        commands[command_count].description = description;
        commands[command_count].execute = execute;
        command_count++;
    }
}

// выполнение команды по входной строке
// парсит команду и аргументы, находит и выполняет соответствующую функцию
int execute_command(const char* input) {
    if (!input || strlen(input) == 0) {
        return 0; // пустая строка - ничего не делаем
    }
    
    // копируем входную строку для обработки
    char cmd_line[256];
    strcpy(cmd_line, input);
    
    // находим команду (первое слово)
    char* cmd_name = cmd_line;
    char* args = strchr(cmd_line, ' ');
    
    if (args) {
        *args = '\0'; // разделяем команду и аргументы
        args++; // пропускаем пробел
    }
    
    // ищем команду в зарегистрированных
    for (int i = 0; i < command_count; i++) {
        if (strcmp(commands[i].name, cmd_name) == 0) {
            return commands[i].execute(args);
        }
    }
    
    // команда не найдена - выводим ошибку
    char error_msg[256];
    strcpy(error_msg, "Command not found: ");
    strcat(error_msg, cmd_name);
    fash_output("", VGA_USE_GLOBAL_BG);
    fash_output(error_msg, VGA_LIGHT_RED);
    return -1;
} 