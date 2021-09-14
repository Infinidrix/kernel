.code16
load_kernel:
    pushw %bp
    movw %sp, %bp

    pushw $0x1000 # Issue with using a constant so hardcoded 
    pushw $0x15
    call disk_load
    leave
    ret
