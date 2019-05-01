#include "ports.h"
#include "screen.h"
//#include "cpu/isr.h"

void kmain() 
{
	//isr_init();
	clear_screen();
	char* msg = "Hello";
	print(msg, WHITE_ON_BLACK);
	//char* s = "Hello, world!";
	//print(s, RED_ON_WHITE);
}