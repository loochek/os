CC=/home/loochek/opt/cross/bin/i386-elf-gcc
CFLAGS=-ffreestanding -nostdlib -pedantic -Wall -W -Werror
LDFLAGS=
SRCDIR=source
BINDIR=binaries
SOURCES=$(wildcard source/kernel/*.c $(SRCDIR)/kernel/peripherals/*.c $(SRCDIR)/cpu/*.c $(SRCDIR)/libc/*.c)
OBJ=$(addprefix $(BINDIR)/, ${SOURCES:.c=.o} kernel/cpu/interrupt.o)

all: build
	qemu-system-i386 -fda os.bin

$(BINDIR)/os.bin: $(BINDIR)/boot/bootloader.bin $(BINDIR)/kernel/kernel.bin
	cat $^ > os.bin

$(BINDIR)/kernel/kernel.bin: $(BINDIR)/kernel/kernel_entry.o ${OBJ}
	/home/loochek/opt/cross/bin/i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

$(BINDIR)/%.o: $(SRCDIR)/%.c
	${CC} ${CFLAGS} -c $< -o $@
	
$(BINDIR)/%.o: $(SRCDIR)/%.asm
	nasm $< -f elf32 -o $@
	
$(BINDIR)/%.bin: $(SRCDIR)/%.asm
	nasm $< -f bin -o $@

clean:
	rm -rf binaries/boot/*.bin binaries/kernel/*.o binaries/kernel/cpu/*.o binaries/kernel/peripherals/*.o binaries/kernel/*.bin
	rm -rf os.bin
	
build: clean $(BINDIR)/os.bin
