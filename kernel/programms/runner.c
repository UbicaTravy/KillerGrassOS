// не знаю зачем, но пусть будет для запуска программ
// мне просто было нечего делать и я сделал это

#include "runner.h"
#include "../../libs/string.h"

extern void prog_demo(void); // пример программы
extern void prog_kgter(void); // текстовый редактор

typedef struct {
    const char* name;
    program_entry_t entry;
} program_desc_t;

static program_desc_t programs[] = {
    { "demo", prog_demo },
    { "kg", prog_kgter },
};

void program_stop_shell(void) {
    fash_exit();
}

void program_restore_shell(void) {
    fash_restart();
}

static program_entry_t program_find(const char* name) {
    if (!name) return 0;
    for (unsigned i = 0; i < sizeof(programs)/sizeof(programs[0]); i++) {
        if (strcmp(programs[i].name, name) == 0) return programs[i].entry;
    }
    return 0;
}

int program_run(const char* name) {
    program_entry_t entry = program_find(name);
    if (!entry) {
        fash_output("program not found", VGA_LIGHT_RED);
        return -1;
    }
    program_stop_shell();
    // запуск программы
    entry();
    // по возврату из программы включаем оболочку и показываем новый промпт сразу
    program_restore_shell();
    fash_show_prompt("fash> ", fash_get_position(), VGA_LIGHT_GREEN);
    return 0;
}


