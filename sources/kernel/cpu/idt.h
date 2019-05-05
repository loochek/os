#ifndef IDT_H
#define IDT_H

#include <stdint.h>

/* How every interrupt gate (handler) is defined */
struct idt_entry
{
    uint16_t low_offset;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed));

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
struct idt_register
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_register idt_reg;

void set_idt_gate(int n, uint32_t handler);
void set_idt();

#endif
