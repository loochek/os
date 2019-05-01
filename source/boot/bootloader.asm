[org 0x7c00]
[bits 16]

KERNEL_OFFSET  equ 0x1000

xor ax, ax ;init segment registers
mov ds, ax
mov es, ax
mov ss, ax

mov sp, 0x9000 ;set up the stack
mov bp, sp

;load kernel from disk
mov bx, KERNEL_OFFSET
mov dh, 4
call disk_load

;switch to 32-bit protected mode
cli                    ;disable interrupts
lgdt [gdt_descriptor]  ; load GDT
mov eax, cr0           ;|
or eax, 0x1            ;|switch to PM
mov cr0, eax           ;|
jmp CODE_SEG:init_pm   ;continue in protected mode
	
%include "source/boot/gdt.asm"
%include "source/boot/disk.asm"
%include "source/boot/print_real.asm"

[bits 32]
init_pm:
    mov ax, DATA_SEG ;init segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ;set up the stack
    mov esp, ebp
	
	jmp KERNEL_OFFSET ;jump to kernel entry

times 01beh-($-$$) db 00h ; enchantments for shitty firmwares and UEFI CSM
dd 80h
db 01h

times 510-($-$$) db 0 
dw 0xaa55