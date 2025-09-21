#include "commands.h"

// команда color - изменяет цвет фона системы
// принимает аргумент с названием цвета
int cmd_color(const char* args) {
    // выводим пустую строку чтобы не перекрыть промпт
    fash_output("", VGA_WHITE);
    
    if (!args || strlen(args) == 0) {
        fash_output("Usage: color <color_name>", VGA_LIGHT_GREEN);
        fash_output("Available colors:", VGA_WHITE);
        fash_output("  black, blue, green, cyan, red, magenta, brown, light-grey", VGA_WHITE);
        fash_output("  dark-grey, light-blue, light-green, light-cyan, light-red", VGA_WHITE);
        fash_output("  light-magenta, light-brown, white", VGA_WHITE);
        return 0;
    }
    
    unsigned char bg_color = VGA_BLUE; // по умолчанию синий
    
    // определяем цвет по аргументу
    if (strcmp(args, "black") == 0) bg_color = VGA_BLACK;
    else if (strcmp(args, "blue") == 0) bg_color = VGA_BLUE;
    else if (strcmp(args, "green") == 0) bg_color = VGA_GREEN;
    else if (strcmp(args, "cyan") == 0) bg_color = VGA_CYAN;
    else if (strcmp(args, "red") == 0) bg_color = VGA_RED;
    else if (strcmp(args, "magenta") == 0) bg_color = VGA_MAGENTA;
    else if (strcmp(args, "brown") == 0) bg_color = VGA_BROWN;
    else if (strcmp(args, "light-grey") == 0) bg_color = VGA_LIGHT_GREY;
    else if (strcmp(args, "dark-grey") == 0) bg_color = VGA_DARK_GREY;
    else if (strcmp(args, "light-blue") == 0) bg_color = VGA_LIGHT_BLUE;
    else if (strcmp(args, "light-green") == 0) bg_color = VGA_LIGHT_GREEN;
    else if (strcmp(args, "light-cyan") == 0) bg_color = VGA_LIGHT_CYAN;
    else if (strcmp(args, "light-red") == 0) bg_color = VGA_LIGHT_RED;
    else if (strcmp(args, "light-magenta") == 0) bg_color = VGA_LIGHT_MAGENTA;
    else if (strcmp(args, "light-brown") == 0) bg_color = VGA_LIGHT_BROWN;
    else if (strcmp(args, "white") == 0) bg_color = VGA_WHITE;
    else {
        fash_output("Unknown color. Use 'color' without arguments to see available colors.", VGA_LIGHT_RED);
        return -1;
    }
    
    // изменяем цвет фона
    vga_set_background_color_and_clear(bg_color);
    
    char msg[64];
    strcpy(msg, "Background color changed to: ");
    strcat(msg, args);
    fash_output(msg, VGA_LIGHT_GREEN);
    
    return 0;
} 