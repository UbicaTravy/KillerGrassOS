#include "commands.h"

// команда date - показывает текущую дату и время
// в реальной ОС здесь будет чтение из RTC, пока что показывает статичную информацию
int cmd_date(const char* args) {
    (void)args; // игнорируем аргументы
    
    // выводим пустую строку чтобы не перекрыть промпт
    fash_output("", VGA_WHITE);
    
    fash_output("Current date and time:", VGA_LIGHT_GREEN);
    fash_output("Date: January 1, 2025", VGA_WHITE);
    fash_output("Time: 12:00:00 UTC", VGA_WHITE);
    fash_output("Day of week: Wednesday", VGA_LIGHT_CYAN);
    fash_output("Note: RTC driver not implemented yet", VGA_LIGHT_RED);
    
    return 0;
} 