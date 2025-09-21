#include "commands.h"
#include "../../drivers/io.h" // outw()

// exit - корректно завершает работу системы
int cmd_exit(const char* args) {
    (void)args; // игнорируем аргументы
    
    // сообщения о завершении
    fash_output("\nInitiating system shutdown...", VGA_LIGHT_MAGENTA);
    fash_output("All processes terminated", VGA_LIGHT_RED);
    fash_output("Goodbye from KGOS!", VGA_LIGHT_CYAN);
    
    // анимация завершения
    for (int i = 0; i < 5; i++) {
        fash_output(".", VGA_WHITE);
        for (volatile int j = 0; j < 500000; j++);
    }
    
    // попытка выключения через разные методы
    fash_output("\nAttempting system shutdown...", VGA_LIGHT_GREEN);
    
    // стандартный метод для QEMU
    outw(0x604, 0x2000);  // QEMU-specific shutdown
    
    // альтернативный метод для Bochs/QEMU
    outw(0xB004, 0x2000);  // Bochs and older QEMU
    
    // ACPI shutdown (если поддерживается ваще)))))
    outw(0x4004, 0x3400);
    
    // Magic breakpoint для отладки
    asm volatile("xchg %bx, %bx");
    
    // Fallback - вечный цикл с HLT
    fash_output("\nSystem halted. You may now turn off power.", VGA_LIGHT_GREEN);
    while(1) {
        asm volatile ("cli\nhlt");
    }
    
    return 0;
}