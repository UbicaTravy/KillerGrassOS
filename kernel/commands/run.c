#include "commands.h"
#include "../programms/runner.h"

int cmd_run(const char* args) {
    if (!args || !*args) {
        fash_output("usage: run <program>", VGA_LIGHT_RED);
        return -1;
    }
    return program_run(args);
}


