CC=i686-elf-gcc
CFLAGS=-ffreestanding -pedantic -Wall -W -Werror -ggdb
LDFLAGS=
SRCDIR=sources
BINDIR=binaries
SOURCES=$(wildcard $(SRCDIR)/kernel/*.c $(SRCDIR)/kernel/peripherals/*.c $(SRCDIR)/kernel/cpu/*.c $(SRCDIR)/kernel/libc/*.c)
OBJ=${SOURCES:$(SRCDIR)%.c=$(BINDIR)%.o} $(BINDIR)/kernel/cpu/interrupt.o

all: build
	qemu-system-i386 -fda os.bin

$(BINDIR)/os.bin: $(BINDIR)/boot/bootloader.bin $(BINDIR)/kernel/kernel.bin
	cat $^ > os.bin

$(BINDIR)/kernel/kernel.elf: $(BINDIR)/kernel/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^
	
$(BINDIR)/kernel/kernel.bin : $(BINDIR)/kernel/kernel.elf
	i686-elf-objcopy -O binary $^ $@
	
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
