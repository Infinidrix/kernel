.code16
switch_to_pm:
cli

movw $0, %ax
movw %ax, %ds

lgdt GDT_DESCRIPTOR

movl %cr0, %eax
or $0x1, %al
movl %eax, %cr0

ljmp $0x10, $init_pm

.code32
init_pm:
    movw $0x8, %ax
    movw %ax, %ds
    movw %ax, %ss
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movl $0x90000, %ebp
    movl %ebp, %esp

    call BEGIN_PM
    jmp hang
    