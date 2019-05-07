#include "peripherals/ports.h"
#include "peripherals/screen.h"
#include "cpu/isr.h"
#include "peripherals/keyboard.h"
#include "libc/string.h"
#include "libc/mem.h"
#include "stdint.h"
#include "fs/ramfs.h"

static char welcome[] = "\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n\xba     govnoOS preprealpha 1     \xba\n\xba       2019     loochek        \xba\n\xba                               \xba\n\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\n";

extern unsigned char _binary_ramfs_bin_start[];

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
    else if (strcmp(cmd, "MEMTEST") == 0)
    {
        for (;;)
        {
            unsigned char* memptr = malloc(4096);
            char buf[20];
            htoa((int)memptr, buf);
            print("0x");
            print(buf);
            print(" ");
            for (int i = 0; i < 16384; i++)
                *(memptr + i) = 'a';
            int passed = 1;
            for (int i = 0; i < 16384; i++)
            {
                if (*(memptr + i) != 'a')
                {
                    passed = 0;
                    break;
                }
            }
            if (passed)
                print("passed\n");
            else
            {
                print("failed\n");
                break;
            }
        }

    }
    else if (strcmp(cmd, "FS") == 0)
    {
        fs_header* header = (fs_header*)_binary_ramfs_bin_start;
        dir_node *dir = (dir_node*) (header->root_offset + _binary_ramfs_bin_start);
        print_dir(dir, (uint32_t) _binary_ramfs_bin_start);

    }
    else
    {
        print("Undefined command: ");
        print(cmd);
        print("\n");
    }
    print("govnoOS>");
}
