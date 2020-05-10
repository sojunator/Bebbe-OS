#include "int.h"
#include "mem.h"
#include "tty.h"

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */


/* This installs a custom IRQ handler for the given IRQ */
void irqInstallHandler(int irq, void (*handler)(struct regs *r))
{
	irq_routines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void irqUninstallHandler(int irq)
{
	irq_routines[irq] = 0;
}



void idtSetGate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
   idt[num].base_lo = (base & 0xFFFF);
   idt[num].base_hi = (base >> 16) & 0xFFFF;
   idt[num].always0 = 0x0;
   idt[num].sel = sel;
   idt[num].flags = flags;
}




void isrsInstall()
{
   idtSetGate(0,  (uint32_t)_isr0, 0x08, 0x8E);
   idtSetGate(1,  (uint32_t)_isr1, 0x08, 0x8E);
   idtSetGate(2,  (uint32_t)_isr2, 0x08, 0x8E);
   idtSetGate(3,  (uint32_t)_isr3, 0x08, 0x8E);
   idtSetGate(4,  (uint32_t)_isr4, 0x08, 0x8E);
   idtSetGate(5,  (uint32_t)_isr5, 0x08, 0x8E);
   idtSetGate(6,  (uint32_t)_isr6, 0x08, 0x8E);
   idtSetGate(7,  (uint32_t)_isr7, 0x08, 0x8E);
   idtSetGate(8,  (uint32_t)_isr8, 0x08, 0x8E);
   idtSetGate(9,  (uint32_t)_isr9, 0x08, 0x8E);
   idtSetGate(10, (uint32_t)_isr10, 0x08, 0x8E);
   idtSetGate(11, (uint32_t)_isr11, 0x08, 0x8E);
   idtSetGate(12, (uint32_t)_isr12, 0x08, 0x8E);
   idtSetGate(13, (uint32_t)_isr13, 0x08, 0x8E);
   idtSetGate(14, (uint32_t)_isr14, 0x08, 0x8E);
   idtSetGate(15, (uint32_t)_isr15, 0x08, 0x8E);
   idtSetGate(16, (uint32_t)_isr16, 0x08, 0x8E);
   idtSetGate(17, (uint32_t)_isr17, 0x08, 0x8E);
   idtSetGate(18, (uint32_t)_isr18, 0x08, 0x8E);
   idtSetGate(19, (uint32_t)_isr19, 0x08, 0x8E);
   idtSetGate(20, (uint32_t)_isr20, 0x08, 0x8E);
   idtSetGate(21, (uint32_t)_isr21, 0x08, 0x8E);
   idtSetGate(22, (uint32_t)_isr22, 0x08, 0x8E);
   idtSetGate(23, (uint32_t)_isr23, 0x08, 0x8E);
   idtSetGate(24, (uint32_t)_isr24, 0x08, 0x8E);
   idtSetGate(25, (uint32_t)_isr25, 0x08, 0x8E);
   idtSetGate(26, (uint32_t)_isr26, 0x08, 0x8E);
   idtSetGate(27, (uint32_t)_isr27, 0x08, 0x8E);
   idtSetGate(28, (uint32_t)_isr28, 0x08, 0x8E);
   idtSetGate(29, (uint32_t)_isr29, 0x08, 0x8E);
   idtSetGate(30, (uint32_t)_isr30, 0x08, 0x8E);
   idtSetGate(31, (uint32_t)_isr31, 0x08, 0x8E);

}

void irqInstall()
{
   idtSetGate(32, (unsigned) _irq0, 0x08, 0x8E);
   idtSetGate(33, (unsigned) _irq1, 0x08, 0x8E);
   idtSetGate(34, (unsigned) _irq2, 0x08, 0x8E);
   idtSetGate(35, (unsigned) _irq3, 0x08, 0x8E);
   idtSetGate(36, (unsigned) _irq4, 0x08, 0x8E);
   idtSetGate(37, (unsigned) _irq5, 0x08, 0x8E);
   idtSetGate(38, (unsigned) _irq6, 0x08, 0x8E);
   idtSetGate(39, (unsigned) _irq7, 0x08, 0x8E);
   idtSetGate(40, (unsigned) _irq8, 0x08, 0x8E);
   idtSetGate(41, (unsigned) _irq9, 0x08, 0x8E);
   idtSetGate(42, (unsigned) _irq10, 0x08, 0x8E);
   idtSetGate(43, (unsigned) _irq11, 0x08, 0x8E);
   idtSetGate(44, (unsigned) _irq12, 0x08, 0x8E);
   idtSetGate(45, (unsigned) _irq13, 0x08, 0x8E);
   idtSetGate(46, (unsigned) _irq14, 0x08, 0x8E);
   idtSetGate(47, (unsigned) _irq15, 0x08, 0x8E);

}




void isrHandler(struct regs *r)
{

   char* exception_messages[] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",

	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",

	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",

	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
   };

	/* Is this a fault whose number is from 0 to 31? */
	if (r->int_no < 32)
	{
		/* Display the description for the Exception that occurred.
		*  In this tutorial, we will simply halt the system using an
		*  infinite loop */

		printf("0x%x \n", (uint32_t)r->err_code);
		printf("ADDR: 0x%x\n", getCR2());
		printf(exception_messages[r->int_no]);

		printf("Exception. System Halted!\n");

	}
}

void irqHandler(struct regs *r)
{
	/* This is a blank function pointer */
	void (*handler)(struct regs *r);

	/* Find out if we have a custom handler to run for this
	*  IRQ, and then finally, run it */

	handler = irq_routines[r->int_no - 32];
	if (handler)
	{
		handler(r);
	}

	/* If the IDT entry that was invoked was greater than 40
	*  (meaning IRQ8 - 15), then we need to send an EOI to
	*  the slave controller */
	if (r->int_no >= 40)
	{
		outb(0xA0, 0x20);
	}

	/* In either case, we need to send an EOI to the master
	*  interrupt controller too */
	outb(0x20, 0x20);
}

uint32_t tick = 0;
void clockHandler(struct regs *r)
{
 	//terminal_writestring("Ropade po ratt handler");
}

void initIdt()
{

	/* Sets the special IDT pointer up, just like in 'gdt.c' */

	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
	idtp.base = (unsigned int)&idt;

	memset( (unsigned char*) &idt, 0, sizeof(struct idt_entry) * 256);

	// Remap the irq table.
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);

	irqInstall();
	isrsInstall();

	irqInstallHandler(0, clockHandler);

   __asm__ __volatile__("\n\
	  movl %[tab], %%eax     \n\
	  lidt (%%eax)            \n\
	  sti                    # Enable interrupts   \n\
	  " : : [tab] "p" (&idtp) : "%eax");

   printf("IDT table installed \n");
}

