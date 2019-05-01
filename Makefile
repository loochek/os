CC=i686-elf-gcc
CFLAGS=-ffreestanding -nostdlib
LDFLAGS=
SOURCES=kernel/kernel.c kernel/ports.c kernel/screen.c kernel/cpu/idt.c kernel/cpu/isr.c
SRCDIR=source
BINDIR=binaries
OBJ=$(addprefix $(BINDIR)/, ${SOURCES:.c=.o} kernel/cpu/interrupt.o)

all: $(BINDIR)/os.bin

$(BINDIR)/os.bin: $(BINDIR)/boot/bootloader.bin $(BINDIR)/kernel/kernel.bin
	cat $^ > os.bin

$(BINDIR)/kernel/kernel.bin: $(BINDIR)/kernel/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

$(BINDIR)/%.o: $(SRCDIR)/%.c
	${CC} ${CFLAGS} -c $< -o $@
	
$(BINDIR)/%.o: $(SRCDIR)/%.asm
	nasm $< -f elf32 -o $@

$(BINDIR)/%.bin: $(SRCDIR)/%.asm
	nasm $< -f bin -o $@