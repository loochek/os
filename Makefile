CC=i686-elf-gcc
CFLAGS=-ffreestanding -nostdlib -pedantic
LDFLAGS=
SOURCES=kernel/kernel.c kernel/peripherals/ports.c kernel/peripherals/screen.c kernel/cpu/idt.c kernel/cpu/isr.c kernel/stdlib.c kernel/peripherals/keyboard.c
SRCDIR=source
BINDIR=binaries
OBJ=$(addprefix $(BINDIR)/, ${SOURCES:.c=.o} kernel/cpu/interrupt.o)

all: clean $(BINDIR)/os.bin

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

clean:
	rm -rf binaries/boot/*.bin binaries/kernel/*.o binaries/kernel/cpu/*.o binaries/kernel/drivers/*.o binaries/kernel/*.bin
	rm -rf os.bin