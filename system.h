#ifndef SYSTEM__H
#define SYSTEM__H


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern void numberToAscii(uint32_t number, char * buffer, uint8_t base);
extern unsigned char inb (unsigned short _port);
extern void outb (unsigned short _port, unsigned char _data);

#endif
