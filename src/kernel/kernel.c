#include "../drivers/screen.h"
#include "utils.h"
#include "loader.h"
#include "sync.h"
#include "program_control_block.h"

void create_syscall_table();

void main(){ 
    clear_screen();
    create_syscall_table();
    print_attr("Loaded Kernel\n", GREEN_ON_BLACK);
    loader("");
    print_attr("\nI guess I'm done... good bye", YELLOW_ON_BLUE);
}


void create_syscall_table() {
    Syscall_table_t sys_call_table = (Syscall_table_t) SYSCALL_VECTOR;
    sys_call_table[LOADER_NO] = (Syscall_t) loader;
    sys_call_table[PRINTLN_NO] = (Syscall_t) print_attr;
    sys_call_table[PRINT_INT_NO] = (Syscall_t) print_int_attr;
    sys_call_table[MUTEX_INIT_NO] = (Syscall_t) mutex_init;
    sys_call_table[MUTEX_LOCK_NO] = (Syscall_t) mutex_lock;
    sys_call_table[MUTEX_UNLOCK_NO] = (Syscall_t) mutex_unlock;
    sys_call_table[SEM_INIT_NO] = (Syscall_t) semaphore_init;
    sys_call_table[SEM_WAIT_NO] = (Syscall_t) semaphore_wait;
    sys_call_table[SEM_POST_NO] = (Syscall_t) semaphore_post;
    sys_call_table[GET_PID_NO] = (Syscall_t) getpid;
    sys_call_table[GET_TID_NO] = (Syscall_t) gettid;
    sys_call_table[THREAD_EXIT_NO] = (Syscall_t) pthread_exit;
    sys_call_table[THREAD_CREATE_NO] = (Syscall_t) pthread_create;
    sys_call_table[THREAD_YIELD_NO] = (Syscall_t) pthread_yield;
}