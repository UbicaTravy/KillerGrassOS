#ifndef PROGRAM_RUNNER_H
#define PROGRAM_RUNNER_H

#include "../../drivers/vga.h"
#include "../../drivers/keyboard.h"
#include "../../drivers/fash.h"
#include "../../libs/types.h"

typedef void (*program_entry_t)(void);

void program_stop_shell(void);
void program_restore_shell(void);
int program_run(const char* name);

#endif

