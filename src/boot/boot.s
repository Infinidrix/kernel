# Don't change this part - 46 . rept
# The only file you should change is the  16_bit/print_string.s file
.code16                 #generate 16-bit code
.text                   #executable code location
.globl _start;
_start:                 #code entry point
    movb %dl, BOOT_DRIVE

    movw $0x8000, %bp
    movw %bp, %sp
     
    pushw $0x9000
    pushw BOOT_DRIVE
    pushw $0x05
    call disk_load

    pushw 0x9000
    call print_hex

    pushw 0x9512
    call print_hex

    jmp hang 

.include "src/boot/utils-16/print_str.s"
.include "src/boot/utils-16/print_hex.s"
.include "src/boot/utils-16/disk_loader.s"

BOOT_DRIVE:
    .byte 0

hello_msg:
    .asciz "Hello There! General Kenobi!!!\n"


# Don't change anything below this
hang:
    jmp hang

. = _start + 510        #mov to 510th byte from 0 pos

#The magic number which tells BIOS that this is indeed OS code not junk
magic:
    .2byte 0xaa55

.fill 512,2,0xdada
.fill 512,2,0xface
 
