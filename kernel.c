#include "multiboot.h"

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
 
void kernel_main(unsigned long magic, unsigned long addr) 
{
	multiboot_info_t *mbi;

	initSerial();
	initTerminal();
	initGdt();
	initIdt();

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		printf("MAGIC IS NOT MAGIC\n");
		return;
	}

	mbi = (multiboot_info_t *) addr;

	/* Print out the flags. */
	printf ("flags = 0x%x\n", (unsigned) mbi->flags);


	if (mbi->flags & MULTIBOOT_INFO_MEMORY) 
	{
		printf ("mem_lower = %uKB, mem_upper = %uKB\n",
				(unsigned) mbi->mem_lower, (unsigned) mbi->mem_upper);
 
	}

	if (mbi->flags & MULTIBOOT_INFO_MEM_MAP)
	{
	  multiboot_memory_map_t *mmap;
	  
	  printf ("mmap_addr = 0x%x, mmap_length = 0x%x\n",
			  (unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);

	  for (mmap = (multiboot_memory_map_t *) mbi->mmap_addr; (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
		   mmap = (multiboot_memory_map_t *) ((unsigned long) mmap + mmap->size + sizeof (mmap->size)))
		{
			printf (" size = 0x%x, base_addr = 0x%x,"
					" length = 0x%x, type = 0x%x\n",
					(unsigned) mmap->size,
					(unsigned) (mmap->addr >> 32),
					(unsigned) (mmap->addr & 0xffffffff),
					(unsigned) (mmap->len >> 32),
					(unsigned) (mmap->len & 0xffffffff),
					(unsigned) mmap->type);
		}
	}

	initPaging();  
 


	for(;;) {
		asm("hlt");
	}
}
