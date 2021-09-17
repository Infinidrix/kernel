#include "../drivers/screen.h"
#include "utils.h"
#include "loader.h"

void create_syscall_table();

void main(){ 
    clear_screen();
    create_syscall_table();
    // Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
    // Syscall_t syscall_func = syscall_table[PRINTLN_NO];
    // syscall_func("Coool  ", WHITE_ON_BLACK);
    print("Loaded Kernel\n");
    // syscall_func = syscall_table[PRINT_INT_NO];
    // syscall_func((void *)2001,GREEN_ON_BLACK);
    loader("");
}


void create_syscall_table() {
    Syscall_table_t sys_call_table = (Syscall_table_t) SYSCALL_VECTOR;
    sys_call_table[LOADER_NO] = (Syscall_t) loader;
    sys_call_table[PRINTLN_NO] = (Syscall_t) print_attr;
    sys_call_table[PRINT_INT_NO] = (Syscall_t) print_int_attr;
}