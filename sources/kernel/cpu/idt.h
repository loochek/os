#ifndef IDT_H
#define IDT_H

/* How every interrupt gate (handler) is defined */
struct idt_entry
{
    unsigned short low_offset;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short high_offset;
} __attribute__((packed));

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
struct idt_register
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_register idt_reg;

void set_idt_gate(int n, unsigned int handler);
void set_idt();

#endif
