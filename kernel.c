#include "mem.h"
#include "tty.h"
#include "int.h"
#include "serial.h"


//#include "multiboot.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 

extern uint32_t * freeList;


void kernel_main(uint32_t* multiboot) 
{
	initSerial();
	initTerminal();
 	initGdt();
	initIdt();
	initPaging();  
 	uint32_t * pageTest = (uint32_t*)(0x3E80000 + 0x1000);

 	*pageTest = 45;




 	for(;;) {
    	asm("hlt");
 	}
}
