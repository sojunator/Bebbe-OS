#ifndef INT__H
#define INT__H

#include "system.h"

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit; // Protection
    unsigned int base;
} __attribute__((packed));

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};





struct idt_entry idt[256];
struct idt_ptr idtp;


void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

void init_idt();

void irq_install();

void isrs_install();

void isr_handler(struct regs *r);

void irq_handler(struct regs *r);

#endif