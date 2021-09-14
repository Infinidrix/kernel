.code32
.globl main
call main
jmp hang

hang:
    jmp hang