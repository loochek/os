#include "ports.h"
#include "screen.h"
#include "cpu/isr.h"

void kmain() 
{
	isr_install();
	clear_screen();
	char* msg = "Hello\n";
	print(msg, WHITE_ON_BLACK);
	__asm__ __volatile__("int $2");
	__asm__ __volatile__("int $3");
}