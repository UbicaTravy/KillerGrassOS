// -----------------------------------------------
// FecalOS Main — краткое описание и справка
// -----------------------------------------------

// Вот тут будет вся логика ОС.
// В будущем здесь будет много всего интересного.

// -----------------------------------------------
// ОС и её логика
// -----------------------------------------------

// "Что такое ОС?"
// ОС (Operating System) — это система, которая управляет всеми процессами и ресурсами.
// ОС также отвечает за загрузку и выгрузку программ и данных.
// ОС также отвечает за взаимодействие с аппаратными ресурсами, такими как процессор, память, диски и сеть. За безопасность и защиту системы от внешних угроз и вообще всё.

// "Что такое ядро?"
// См. в kernel.c

// FecalOS Main
// Author: KillerGrass

#include "drivers/vga.h" // подключаем драйвер VGA
#include "types.h" // подключаем типы данных

void fecalos_main(void) {
    vga_set_background_color_and_clear(VGA_BLUE); // устанавливаем синий цвет фона

    // сообщения для вывода с индивидуальными цветами фона
    vga_print_centered_with_bg(2, "FecalOS v0.0002 - Simple Boot Test", VGA_LIGHT_GREEN, VGA_USE_GLOBAL_BG); // "FecalOS v0.0002 - Простой тест загрузки"
    vga_print_centered_with_bg(4, "Kernel loaded successfully!", VGA_WHITE, VGA_RED); // "Ядро загружено успешно!"
    vga_print_centered_with_bg(6, "System is running in 32-bit protected mode", VGA_BLACK, VGA_LIGHT_CYAN); // "Система работает в 32-битном защищенном режиме"
    vga_print_centered_with_bg(8, "Created by KillerGrass, 2025", VGA_WHITE, VGA_BLUE); // "Создано KillerGrass, 2025"
    vga_print_centered_with_bg(10, "Created in Russia in Siberia in Altay", VGA_LIGHT_GREEN, VGA_USE_GLOBAL_BG); // "Создано в России в Сибири в Алтае"
    vga_print_centered_with_bg(12, "Print programm for starting", VGA_RED, VGA_WHITE); // "Введите программу для запуска"
    vga_print_centered_with_bg(13, "Fash - FecalOS Shell", VGA_WHITE, VGA_BLUE); // "Fash - FecalOS Shell"
    
    // другие способы вывода сообщений:
    // vga_print_text(x, y, "text", color) — выводит текст в заданную позицию
    // vga_print_centered(y, "text", color) — выводит текст по центру в заданной строке
    // vga_print_centered_with_bg(y, "text", text_color, bg_color) — выводит текст по центру в заданной строке с заданным цветом текста и фона
    // vga_print_text_with_bg(x, y, "text", text_color, bg_color) — выводит текст в заданную позицию с заданным цветом текста и фона
    // vga_put_char(x, y, 'A', color) — выводит символ в заданную позицию с заданным цветом
    // vga_put_char_with_bg(x, y, 'A', text_color, bg_color) — выводит символ в заданную позицию с заданным цветом текста и фона

    // чтобы ОС не завершалась, мы создаём бесконечный цикл
    while(1) {
        for (volatile int i = 0; i < 1000000; i++);
    }
} 