.code32
.globl main
.globl _start
_start:
    call main
    ret

hang:
    jmp hang
