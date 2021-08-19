print_str:
    pushw %bp
    movw %sp, %bp

    movb $0x0e, %ah
    movw 4(%bp), %bx

  loop_start:
    mov (%bx), %al
    cmp $0x0, %al
    je end
    int $0x10

    inc %bx
    jmp loop_start
  end:
    leave
    ret
