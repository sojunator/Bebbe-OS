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
 
void terminal_initialize(void) 
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
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	if (c == '\n')
	{
		terminal_column = 0;
		++terminal_row;
		return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
	return;
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

// I don't care about bases, so it's all decimal if you ask me
void numberToAscii(uint32_t number, char * buffer, uint8_t base)
{
	uint32_t i = 0;
	while(number != 0)
	{
		// 0 is 48 in ascii
		uint8_t val = (number % base);


		// 55 is 10 away from A, so if val is 10, we get A
		buffer[i++] = (val < 10 ? 48 : 55) + val;
		number /= base;
	}
 
	
	for (uint32_t j = 0; j < i / 2; j++)
	{
		// -1 is due to us not wanting the null byte
		char tempswap = buffer[j];
		buffer[j] = buffer[(i - 1) - j];
		buffer[(i - 1) - j] = tempswap;
	}
	 

	buffer[i] = '\0';
	// Buffer will list the number backwards
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
					numberToAscii(va_arg(args, uint32_t), buffer, 10); 

					terminal_writestring(buffer);	
					break;

				case '%':
				case 'c':
					// since char will be turned into a int
					terminal_putchar( * (va_arg(args, char*)));
					break;

				case 's':
					terminal_writestring(va_arg(args, char*));
					break;

				case 'x':
					numberToAscii(va_arg(args, uint32_t), buffer, 16); 
					terminal_writestring(buffer);	

					break;
			}
		}
		else
		{
			terminal_putchar(c);
		}
	}
	
	va_end(args);
}
