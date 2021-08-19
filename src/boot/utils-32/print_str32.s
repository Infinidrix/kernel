.code32

VIDEO_MEMORY:
    .4byte 0xb8000
WHITE_ON_BLACK:
    .byte 0x0f

print_str32:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %ebx

    movl VIDEO_MEMORY, %edx
PRINT32_LOOP_START:
    movb (%ebx), %al
    movb WHITE_ON_BLACK, %ah

    cmp $0x00, %al
    je PRINT32_LOOP_END

    movw %ax, (%edx)

    add $1, %ebx
    add $2, %edx

    jmp PRINT32_LOOP_START
PRINT32_LOOP_END:
    leave
    ret
