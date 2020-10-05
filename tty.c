#include "tty.h"


uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void initTerminal(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminalSetcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminalPutentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
 
	outb(0x3f8,c); 
 
}
 
void terminalPutchar(char c) 
{
	if (c == '\n')
	{ 
		// We need to print this for the logs
		outb(0x3f8,c);
 
		terminal_column = 0;
		++terminal_row;
		return;
	}

	terminalPutentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
	return;
}
 
void terminalWrite(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminalPutchar(data[i]);
}
 
void terminalWritestring(const char* data) 
{
	terminalWrite(data, strlen(data));
}


void printf(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	char c;
	while( (c = *(fmt++)) != '\0')
	{ 
		if (c == '%') 
		{
			c = *(fmt++);
			char buffer[32]; // Just a temp buffer that can hold a large int


			switch (c)
			{
				case 'd':
				case 'i':
				case 'u':
					numberToAscii(va_arg(args, uint32_t), buffer, 10); 
					terminalWritestring(buffer);	

					break;

				case '%':
				case 'c':
					// since char will be turned into a int
					terminalPutchar( * (va_arg(args, char*)));

					break;
				case 's':
					terminalWritestring(va_arg(args, char*));

					break;
				case 'x':
					numberToAscii(va_arg(args, uint32_t), buffer, 16); 
					terminalWritestring(buffer);	

					break;
			}
		}
		else
		{
			terminalPutchar(c);
		}
	}
	
	va_end(args);
}
