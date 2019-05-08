#include "peripherals/ports.h"
#include "peripherals/screen.h"
#include "cpu/isr.h"
#include "peripherals/keyboard.h"
#include "libc/string.h"
#include "libc/mem.h"
#include "stdint.h"
#include "storage/ata.h"

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

/* on Primary bus: ctrl->base =0x1F0, ctrl->dev_ctl =0x3F6. REG_CYL_LO=4, REG_CYL_HI=5, REG_DEVSEL=6 */
int detect_devtype (int slavebit)
{	/* waits until master drive is ready again */
    port_byte_out(0x1F0 + 6, 0xA0 | slavebit<<4);
    port_byte_in(0x3F6);			/* wait 400ns for drive select to work */
    port_byte_in(0x3F6);
    port_byte_in(0x3F6);
    port_byte_in(0x3F6);
    unsigned cl=port_byte_in(0x1F0 + 4);	/* get the "signature bytes" */
    unsigned ch=port_byte_in(0x1F0 + 4);

    /* differentiate ATA, ATAPI, SATA and SATAPI */
    if (cl==0x14 && ch==0xEB) return 0;
    if (cl==0x69 && ch==0x96) return 1;
    if (cl==0 && ch == 0) return 2;
    if (cl==0x3c && ch==0xc3) return 3;
    return 4;
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
        char sector[512];
        read_lba28(0, 1, sector);
        print(sector);
    }
    else
    {
        print("Undefined command: ");
        print(cmd);
        print("\n");
    }
    print("govnoOS>");
}
