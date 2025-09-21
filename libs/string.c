// -----------------------------------------------
// KillerGrass OS (KGOS) String — краткое описание и справка
// -----------------------------------------------

// Этот файл содержит функции для работы со строками.
// Он заменяет стандартные библиотеки в freestanding окружении.

// Он нужен для того чтобы не было ошибки линковки.
// Потому что в freestanding окружении нет стандартных библиотек.
// Поэтому мы пишем свои функции для работы со строками.

#ifndef STRING_C
#define STRING_C

#include "string.h" // подключаем заголовочный файл

// strlen — возвращает длину строки
size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// strcpy — копирует строку src в dest
char* strcpy(char* dest, const char* src) {
    char* ptr = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return ptr;
}

// strchr — ищет первое вхождение символа c в строку str
char* strchr(const char* str, int c) {
    while (*str != '\0') {
        if (*str == (char)c) {
            return (char*)str;
        }
        str++;
    }
    return NULL;
}

// strcmp — сравнивает две строки
int strcmp(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return (*str1 < *str2) ? -1 : 1;
        }
        str1++;
        str2++;
    }
    if (*str1 == '\0' && *str2 == '\0') {
        return 0;
    }
    return (*str1 == '\0') ? -1 : 1;
}

// strcat — конкатенирует две строки
char* strcat(char* dest, const char* src) {
    char* ptr = dest;
    while (*dest != '\0') {
        dest++;
    }
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return ptr;
}

// memset — заполняет память значением
void* memset(void* ptr, int value, size_t num) {
    unsigned char* p = (unsigned char*)ptr;
    for (size_t i = 0; i < num; i++) {
        p[i] = (unsigned char)value;
    }
    return ptr;
}

// memcpy — копирует память из src в dest
void* memcpy(void* dest, const void* src, size_t num) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for (size_t i = 0; i < num; i++) {
        d[i] = s[i];
    }
    return dest;
}

#endif // STRING_C