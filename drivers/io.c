// -----------------------------------------------
// KillerGrass OS (KGOS) IO Functions
// -----------------------------------------------

// функции ввода-вывода - работа с портами
// обеспечивают взаимодействие с аппаратными устройствами

#include "io.h"

// запись байта в порт
// отправляет байт данных в указанный порт
void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// чтение байта из порта
// читает байт данных из указанного порта
unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// запись слова в порт
// отправляет слово (16 бит) в указанный порт
void outw(unsigned short port, unsigned short value) {
    __asm__ volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

// чтение слова из порта
// читает слово (16 бит) из указанного порта
unsigned short inw(unsigned short port) {
    unsigned short ret;
    __asm__ volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}