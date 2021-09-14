.code32
.globl main
.globl _start
_start:
    call main
    jmp hang

hang:
    jmp hang
