#include "peripherals/ports.h"
#include "peripherals/screen.h"
#include "cpu/isr.h"
#include "peripherals/keyboard.h"
#include "libc/string.h"

static char welcome[] = "\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\xba     govnoOS preprealpha 1     \xba\n\xba       2019     loochek        \xba\n\xba                               \xba\n\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\n";

void kmain() 
{
    clear_screen();
    print("Starting govnoOS...\n");
	isr_install();
    print("Set up interrupts\n");
	init_keyboard();
    print("Set up keyboard\n");
    print(welcome);
    print("govnoOS>");
}

void handle_user_input(char cmd[])
{
    if (strcmp(cmd, "") == 0)
        asm("nop");
    else if (strcmp(cmd, "CLEAR") == 0)
        clear_screen();
    else if (strcmp(cmd, "HALT") == 0)
    {
        print("Stopping the CPU...\n");
        asm volatile("cli");
        asm volatile("hlt");
    }
    else
    {
        print("Undefined command: ");
        print(cmd);
        print("\n");
    }
    print("govnoOS>");
}
