#include "system.h"
#include <stdint.h>
int strlen(const char *str)
{
	uint32_t len = 0;
	while (*str != '\0')
	{	
		len++;
		str++;
	}

	return len;
}

void numberToAscii(uint32_t number, char * buffer, uint8_t base)
{
	uint32_t i = 0;

	if (number == 0)
		buffer[i++] = 48;

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
}

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
	for (uint32_t i = 0; i < (uint32_t) count; i++)
	{
		dest[i] = src[i];
	}

	return dest;
}


unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
	for (uint32_t i = 0; i < (uint32_t) count; i++)
		dest[i] = val;	

	return dest;
}



unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
	for (uint32_t i = 0; i <  (uint32_t) count; i++)
		dest[i] = val;

	return dest;
}


unsigned char inb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}


