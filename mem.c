#include "mem.h"
#include "tty.h"


gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
 

// Set the value of one GDT entry.

void gdt_set_gate(uint32_t num,uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
} 


void init_gdt()
{
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (uint32_t)&gdt_entries;

   gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   //gdt_flush((uint32_t)&gdt_ptr);
   load_gdt();
}

void load_gdt()
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

