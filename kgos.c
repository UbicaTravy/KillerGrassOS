// -----------------------------------------------
// KillerGrass OS (KGOS) - основная логика ОС
// -----------------------------------------------

// основной файл ОС - содержит всю логику работы системы
// управляет инициализацией и основным циклом ОС

// -----------------------------------------------
// что такое ОС и ядро
// -----------------------------------------------

// ОС (Operating System) - система управления ресурсами компьютера
// отвечает за загрузку программ, управление памятью и взаимодействие с железом
// ядро - центральная часть ОС, которая работает в привилегированном режиме

// KillerGrass OS (KGOS) Main
// Author: KillerGrass

#include "drivers/vga.h" // драйвер для работы с видео
#include "drivers/keyboard.h" // драйвер для работы с клавиатурой
#include "drivers/fash.h" // драйвер для работы с fash
#include "libs/types.h" // определения типов данных
#include "libs/string.h" // функции для работы со строками
#include "kernel/commands/commands.h" // система команд
#include "kernel/input.h" // модуль управления вводом
#include "kernel/logo.h" // модуль отображения логотипа

#define FASH_START_Y 15  // начальная позиция fash

// главная функция ОС
// инициализирует систему и запускает основной цикл
void kgos_main(void) {
    // отладочная информация
    vga_print_centered(4, "KGOS main started", VGA_LIGHT_YELLOW);
    
    // устанавливаем синий цвет фона
    // оставляем текстовый режим видимым; VBE используем позже при необходимости
    vga_set_background_color_and_clear(VGA_BLUE);
    
    vga_print_centered(5, "Background set to blue", VGA_WHITE);

    // инициализируем драйверы и модули
    vga_print_centered(6, "Initializing drivers...", VGA_LIGHT_CYAN);
    
    keyboard_init();
    vga_print_centered(7, "Keyboard initialized", VGA_WHITE);
    
    fash_init();
    vga_print_centered(8, "Fash initialized", VGA_WHITE);
    
    commands_init();
    vga_print_centered(9, "Commands initialized", VGA_WHITE);
    
    input_init();
    vga_print_centered(10, "Input initialized", VGA_WHITE);

    vga_clear_screen();

    // инициализация fash

    // лого и инфа о системе
    vga_print_centered(11, "Displaying logo...", VGA_LIGHT_CYAN);
    logo_display();
    
    // fash
    fash_set_position(FASH_START_Y);
    
    // первый промпт
    fash_show_prompt("fash> ", fash_get_position(), VGA_LIGHT_GREEN);


    // основной цикл обработки ввода
    // постоянно проверяет клавиатуру и обрабатывает ввод
    while(1) {
        // опрашиваем контроллер клавиатуры и читаем скан-код
        unsigned char scancode = keyboard_read_scancode();
        if (scancode) {
            char c = keyboard_scancode_to_ascii(scancode);
            input_process_key(scancode, c);
        }
        
        // небольшая задержка для снижения нагрузки на CPU
        // если не нравиться уберите и всё
        // я это не убираю потому что хочу на компе 1995 года проверить ОС
        // а вы как хотите
        for (volatile int i = 0; i < 10000; i++);
    }
} 