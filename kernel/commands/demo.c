#include "commands.h"
#include "../programms/runner.h"

int cmd_demo(const char* args) {
    (void)args;
    return program_run("demo");
}


