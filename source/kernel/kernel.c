#include "peripherals/ports.h"
#include "peripherals/screen.h"
#include "cpu/isr.h"
#include "peripherals/keyboard.h"

void kmain() 
{
	isr_install();
	asm volatile("sti");
	init_keyboard();
	clear_screen();
	char* msg = "Hello\n";
	print(msg);
	__asm__ __volatile__("int $2");
	__asm__ __volatile__("int $3");
}
