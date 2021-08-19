# Don't change this part - 46 . rept
# The only file you should change is the  16_bit/print_string.s file
.code16                 #generate 16-bit code
.text                   #executable code location
.globl _start;
_start:                 #code entry point
    
    movb %dl, BOOT_DRIVE

    movw $0x9000, %bp
    movw %bp, %sp

    pushw $hello_msg
    call print_str

    call load_kernel

    call switch_to_pm

    jmp hang 

.include "src/boot/utils-16/print_str.s"
.include "src/boot/utils-16/print_hex.s"
.include "src/boot/utils-16/disk_loader.s"
.include "src/boot/utils-16/gdt.s"
.include "src/boot/utils-16/switch_to_pm.s"
.include "src/boot/utils-32/print_str32.s"

.code16
load_kernel:
    pushw %bp
    movw %sp, %bp
    pushw $0x1000
    pushw BOOT_DRIVE
    pushw $0x15
    call disk_load
    leave
    ret

.code32
BEGIN_PM:
    pushl $new_msg
    call print_str32
    call 0x1000
    jmp hang

hello_msg:
    .asciz "Welcome to 16 bit land, hope you enjoy your transit"
BOOT_DRIVE:
    .byte 0

new_msg:
    .asciz "  <- LOOK!! The start of something big. There's a whole 32 bit world out there"

KERNEL_OFFSET:
    .2byte 0x1000
# Don't change anything below this
hang:
    jmp hang

. = _start + 510        #mov to 510th byte from 0 pos

# The magic number which tells BIOS that this is indeed OS code not junk
magic:
    .2byte 0xaa55