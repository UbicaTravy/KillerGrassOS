#include "commands.h"
#include "../../drivers/io.h"
#include "../../drivers/fash.h"
#include "../../drivers/vga.h"

// Команда reboot - перезагружает систему через ACPI или 8042 контроллер
int cmd_reboot(const char* args) {
    (void)args; // Игнорируем аргументы
    
    // Выводим сообщения с цветами
    fash_output("\nInitiating system reboot...", VGA_LIGHT_RED);
    fash_output("KGOS v0.0003 shutting down", VGA_LIGHT_BLUE);
    fash_output("See you in the next life, comrade!", VGA_LIGHT_GREEN);
    
    // Анимация точки (3 секунды)
    for (int i = 0; i < 3; i++) {
        fash_output(".", VGA_WHITE);
        for (volatile int j = 0; j < 1000000; j++);
    }
    
    // Пробуем разные методы перезагрузки
    // 1. Стандартный метод через 8042 контроллер
    outb(0x64, 0xFE);
    
    // 2. Метод через ACPI (если есть)
    outw(0xB004, 0x2000);
    
    // 3. Тройной fault (крайний случай)
    asm volatile ("cli\n"
                  "mov $0x1000, %esp\n"
                  "push $0x0\n"
                  "push $0x0\n"
                  "iret"); // Вызовет исключение
    
    // Если ничего не сработало - halt
    while(1) {
        asm volatile ("hlt");
    }
    
    return 0;
}