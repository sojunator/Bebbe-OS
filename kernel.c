#include "mem.h"
#include "tty.h"
#include "int.h"
#include "serial.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 

void kernel_main(uint32_t* multiboot) 
{
	initSerial();
	terminal_initialize();
 	initGdt();
	initIdt();
	initPaging();
 
	printf("Testar igen %d \n", 1234); 
 
 	for(;;) {
    	asm("hlt");
 	}
}
