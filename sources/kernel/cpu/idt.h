#ifndef IDT_H
#define IDT_H

#include <stdint.h>

/* How every interrupt gate (handler) is defined */
typedef struct
{
    uint16_t low_offset;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_entry;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
typedef struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register;

idt_entry idt[256];
idt_register idt_reg;

void set_idt_gate(int n, uint32_t handler);
void set_idt();

#endif
