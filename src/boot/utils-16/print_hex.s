print_hex:
    #Setup the stack frame
    pushw %bp
    movw %sp,%bp
    movb $0x5, %al
    movb $0x0, %ah
    movw 4(%bp),%dx

    LOOP_START:
        cmp $0x1, %al
        je END
        
        #The least significant bit
        movw %dx,%di
        and  $0x000F, %di
        movw $hex_nums, %bx     #our base address
        movb (%bx,%di), %ch
        movw $hex_out, %si
        addw %ax, %si
        movb %ch, (%si)
        shr $4, %dx 
        dec %al
        jmp LOOP_START
    END:
        #Call our print string function
        pushw $hex_out
        call print_str
        leave
        ret
    

#This is a string template
hex_out:
    .asciz "0x0000"

hex_nums:
    .ascii "0123456789ABCDEF"
