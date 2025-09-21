#include "commands.h"
#include "../programms/runner.h"

int cmd_kg(const char* args) {
    (void)args;
    return program_run("kg");
}



