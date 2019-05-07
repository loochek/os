#include "idt.h"
#include "../utils.h"

void set_idt_gate(int n, uint32_t handler)
{
	idt[n].low_offset = low_16(handler);
    idt[n].sel = 0x08; //kernel code selector
	idt[n].always0 = 0;
	idt[n].flags = 0x8E;
	idt[n].high_offset = high_16(handler);
}

void set_idt()
{
    idt_reg.base = (uint32_t)& idt;
    idt_reg.limit = 256 * sizeof(idt_entry) - 1;
	/* Don't make the mistake of loading &idt -- always load &idt_reg */
    asm volatile("lidtl (%0)" : : "r" (&idt_reg));
    asm volatile("sti");
}
