// -----------------------------------------------
// FecalOS String — краткое описание и справка
// -----------------------------------------------

// Этот файл содержит функции для работы со строками.
// Он заменяет стандартные библиотеки в freestanding окружении.

#ifndef STRING_H
#define STRING_H

#include "types.h" // собственные типы для standalone ОС

// функции для работы со строками
size_t strlen(const char* str);
char* strcpy(char* dest, const char* src);
char* strchr(const char* str, int c);
int strcmp(const char* str1, const char* str2);
char* strcat(char* dest, const char* src);
void* memset(void* ptr, int value, size_t num);
void* memcpy(void* dest, const void* src, size_t num);

#endif 