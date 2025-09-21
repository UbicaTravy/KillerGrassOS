// -----------------------------------------------
// FecalOS Types — краткое описание и справка
// -----------------------------------------------

// Этот файл содержит собственные определения типов для standalone ОС.
// Он заменяет стандартные библиотеки в freestanding окружении.

// -----------------------------------------------
// Определения типов
// -----------------------------------------------
#ifndef TYPES_H
#define TYPES_H

// целочисленные типы фиксированного размера
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

// размерные типы
typedef uint32_t size_t;
typedef int32_t ssize_t;

// указательные типы
typedef uint32_t uintptr_t;
typedef int32_t intptr_t;

// константы
#define NULL ((void*)0)

// макросы для проверки размера типов
#define UINT8_MAX  255
#define UINT16_MAX 65535
#define UINT32_MAX 4294967295U
#define INT8_MAX   127
#define INT16_MAX  32767
#define INT32_MAX  2147483647

#endif // TYPES_H 