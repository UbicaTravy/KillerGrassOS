// -----------------------------------------------
// KillerGrass OS (KGOS) Logo Module
// -----------------------------------------------

// модуль отображения логотипа - показывает логотип и информацию о системе
// ачё))) ну мне удобнее так выводить свой аху**ый логотип

#include "logo.h"
#include "../drivers/fash.h"

// отображение ASCII-арт логотипа
// выводит логотип FecalOS в виде ASCII-арта
void logo_print_ascii_art(void) {
    vga_print_text_with_bg(0, 1, "  _   ___ _ _           _____                     _____ _____  ", VGA_LIGHT_RED, VGA_USE_GLOBAL_BG);
    vga_print_text_with_bg(0, 2, " | | / (_) | |         |  __ \\                   |  _  /  ___| ", VGA_LIGHT_RED, VGA_USE_GLOBAL_BG);
    vga_print_text_with_bg(0, 3, " | |/ / _| | | ___ _ __| |  \\/_ __ __ _ ___ ___  | | | \\ `--.  ", VGA_LIGHT_RED, VGA_USE_GLOBAL_BG);
    vga_print_text_with_bg(0, 4, " |    \\| | | |/ _ \\ '__| | __| '__/ _` / __/ __| | | | |`--. \\ ", VGA_LIGHT_RED, VGA_USE_GLOBAL_BG);
    vga_print_text_with_bg(0, 5, " | |\\  \\ | | |  __/ |  | |_\\ \\ | | (_| \\__ \\__ \\ \\ \\_/ /\\__/ / ", VGA_LIGHT_RED, VGA_USE_GLOBAL_BG);
    vga_print_text_with_bg(0, 6, " \\_| \\_/_|_|_|\\___|_|   \\____/_|  \\__,_|___/___/  \\___/\\____/  ", VGA_LIGHT_RED, VGA_USE_GLOBAL_BG);
}

// функция для вывода логотипа в командах
// выводит ASCII-арт логотип FecalOS
void print_logo_cmd() {
    fash_output("  _   ___ _ _           _____                     _____ _____  ", VGA_LIGHT_RED);
    fash_output(" | | / (_) | |         |  __ \\                   |  _  /  ___| ", VGA_LIGHT_RED);
    fash_output(" | |/ / _| | | ___ _ __| |  \\/_ __ __ _ ___ ___  | | | \\ `--.  ", VGA_LIGHT_RED);
    fash_output(" |    \\| | | |/ _ \\ '__| | __| '__/ _` / __/ __| | | | |`--. \\ ", VGA_LIGHT_RED);
    fash_output(" | |\\  \\ | | |  __/ |  | |_\\ \\ | | (_| \\__ \\__ \\ \\ \\_/ /\\__/ / ", VGA_LIGHT_RED);
    fash_output(" \\_| \\_/_|_|_|\\___|_|   \\____/_|  \\__,_|___/___/  \\___/\\____/  ", VGA_LIGHT_RED);
}

// отображение логотипа и информации о системе
// показывает полную информацию при загрузке ОС
void logo_display(void) {
    // выводим ASCII-арт логотип
    logo_print_ascii_art();

    // выводим информацию о системе
    vga_print_centered_with_bg(7, "KillerGrass OS v0.0003", VGA_LIGHT_GREEN, VGA_USE_GLOBAL_BG);
    vga_print_centered_with_bg(8, "Kernel loaded successfully!", VGA_WHITE, VGA_USE_GLOBAL_BG);
    vga_print_centered_with_bg(9, "System is running in 32-bit protected mode", VGA_LIGHT_CYAN, VGA_USE_GLOBAL_BG);
    vga_print_centered_with_bg(10, "Created by KillerGrass, 2025", VGA_WHITE, VGA_USE_GLOBAL_BG);
    vga_print_centered_with_bg(11, "Created in Russia in Siberia", VGA_LIGHT_GREEN, VGA_USE_GLOBAL_BG);
    vga_print_text_with_bg(0, 13, "Type 'help' to get started", VGA_LIGHT_GREEN, VGA_USE_GLOBAL_BG);
}