#include "mem.h"
#include "tty.h"


gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
 
uint32_t * freeList;
uint32_t numFree = 0;

// Set the value of one GDT entry.

void gdtSetGate(uint32_t num,uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
} 


void initGdt()
{
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (uint32_t)&gdt_entries;

   /*
      This configures one massive segment 
      from 0x0 to 0xFFFFFFF that both ring0 and ring3
      can read and execute from
   */

   gdtSetGate(0, 0, 0, 0, 0);                // Null segment
   gdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdtSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdtSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
   loadGdt();
}

void loadGdt()
{
   __asm__ __volatile__("                                    \n\
   cli                  # Make sure interrupts are disabled  \n\
   movl %[tab], %%eax   # Get the gdtPtr address             \n\
   lgdt (%%eax)         # Set the GDT                        \n\
   ljmp $0x08, $1f      # Change cs, code segment = 0x08     \n\
   1:                   # Local label as long-jump target    \n\
   movl $16, %%eax      # Set all data segments to 0x10      \n\
   movw %%ax, %%ds                                           \n\
   movw %%ax, %%es                                           \n\
   movw %%ax, %%fs                                           \n\
   movw %%ax, %%gs                                           \n\
   movw %%ax, %%ss                                           \n\
   " : : [tab] "p" (&gdt_ptr) : "%eax");


   terminal_writestring("Loaded GDT\n");
}

void setCR3(uint32_t* page_dir)
{
   __asm__ __volatile__("movl %[dir], %%eax \n\
                       movl %%eax, %%cr3" : : [dir] "r" (page_dir): "%eax");
}

uint32_t * getCR3()
{
   uint32_t * page_dir;
   __asm__ __volatile__("movl %%cr3, %[addr]" : [addr] "=r" (page_dir) : :);
   return page_dir;
}

void enablePaging()
{
 __asm__ __volatile__("movl %%cr0, %%eax       \n\
                       orl $0x80000001, %%eax   \n\
                       movl %%eax, %%cr0" : : : "%eax");
}

uint32_t allocateFrame()
{
   return freeList[numFree--];
}

void freeFrame(uint32_t frame)
{
   freeList[numFree++] = frame;
} 


void initPaging()
{
   uint32_t * page_dir = 0x0;
   setCR3(page_dir); 
   /* Setup tables */

   freeList = (uint32_t*) (0x1000 * 32);

   for (uint32_t i = 0; i < 32; i++)
      freeFrame(0x0 + 0x1000 * i);

   for (uint32_t i = 0; i < 16; i++)
   {
      page_dir[i] = allocateFrame + 0x3;
   }

   // one to one mapping kernel mode
   for (uint32_t i = 0; i < 0x3E80000; i+= 4096)
   {
      uint32_t PT1 = (i >> 22);
      uint32_t PT2 = (i >> 12) & 0x03FF;

      uint32_t * pageTable = page_dir[PT1] & 0xFFFFF000;

      //pageTable[PT2] = i + 0x3;
   }
   
   //enablePaging();
   terminal_writestring("Paging enabled\n");
}
