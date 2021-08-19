disk_load:
    pushw %bp
    movw %sp, %bp

    movb 4(%bp), %dh
    movb 6(%bp), %dl
    movw 8(%bp), %bx
    pushw %dx
    
    movb $0x02, %ah
    movb %dh, %al 
    movb $0x00, %ch
    movb $0x00, %dh
    movb $0x02, %cl

    int $0x13

    jc disk_error

    pop %dx
    cmp %dh, %al

    jne disk_error

    leave
    ret

disk_error:
    pushw $DISK_ERROR_MESSAGE
    call print_str
    jmp hang

DISK_ERROR_MESSAGE:
    .asciz "Disk read error!"

