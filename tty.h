#ifndef TTY__H
#define TTY__H


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "system.h"

  /* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg); 

uint16_t vga_entry(unsigned char uc, uint8_t color); 
 

void initTerminal(void);

void terminalSetcolor(uint8_t color);

void terminalPutentryat(char c, uint8_t color, size_t x, size_t y);

void terminalPutchar(char c);

void terminalWrite(const char* data, size_t size);

void terminalWritestring(const char* data);

void printf(const char* fmt, ...);

#endif