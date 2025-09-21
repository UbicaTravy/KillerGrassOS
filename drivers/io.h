// заголовочный файл для функций ввода-вывода (io.h)
// содержит функции для работы с портами ввода-вывода

// KillerGrass OS (KGOS) IO Functions
// Author: KillerGrass

#ifndef IO_H
#define IO_H

#include "../libs/types.h"

void outb(unsigned short port, unsigned char value);
unsigned char inb(unsigned short port);
void outw(unsigned short port, unsigned short value);
unsigned short inw(unsigned short port);

#endif 