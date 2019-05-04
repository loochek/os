#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#define UNUSED(x) (void)(x)

#define BACKSPACE 0x0E
#define ENTER 0x1C

//static char key_buffer[256];

#define SC_MAX 57
//static const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
//    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
//        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
//        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
//        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
//        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
static const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs)
{
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);

    if (scancode > SC_MAX) return;
//    if (scancode == BACKSPACE) {
//        backspace(key_buffer);
//        kprint_backspace();
    else if (scancode == ENTER)
    {
        print("\n");
        //user_input(key_buffer); /* kernel-controlled function */
        //key_buffer[0] = '\0';
    }
    else
    {
        char letter = sc_ascii[(int)scancode];
        print(&letter);
    }
    UNUSED(regs);
}

void init_keyboard()
{
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
