#include "./syscall_func.h"
#include "../kernel/utils.h"

// void * loader(void * program_file){
//     Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
//     Syscall_t syscall_func = syscall_table[LOADER_NO];
//     return syscall_func(program_file);
// }
/**
 * Print the string str using its attribute atrr
 */
void print_syscall(char * str, Byte_t atrr){
    Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
    Syscall_t syscall_func = syscall_table[PRINTLN_NO];
    syscall_func(str,atrr);
}
/**
 * Print an integer
 */
void print_int_syscall(int num, Byte_t attr){
    Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
    Syscall_t syscall_func = syscall_table[PRINT_INT_NO];
    syscall_func((void *)num,attr);
}
/**
 * Create a new thread.
 */
void pthread_create(thread_t *thread, thread_action action , void * args){
    Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
    Syscall_t syscall_func = syscall_table[THREAD_CREATE_NO];
    syscall_func(thread, action, args);
}
/**
 * Terminates the current thread, and releases any resources
 * that might have been with this thead.
 */
void pthread_exit(){
    Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
    Syscall_t syscall_func = syscall_table[THREAD_EXIT_NO];
    syscall_func(0);
}
/**
 * The yield function. Gives up control of cpu.
 */
void pthread_yield(){
    Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
    Syscall_noarg_t syscall_func = (Syscall_noarg_t) syscall_table[THREAD_YIELD_NO];
    syscall_func();
}

/**
 * Getting this thread's id
 */
Tid_t gettid(){
    Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
    Syscall_t syscall_func = syscall_table[GET_TID_NO];
    return (Tid_t) syscall_func(0);
}
/**
 * Getting the process id
 */
Pid_t getpid(){
    Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
    Syscall_t syscall_func = syscall_table[GET_PID_NO];
    return (Pid_t) syscall_func(0);
}

// void mutex_init(Mutex_t * mutex){
//     Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
//     Syscall_t syscall_func = (Syscall_t) syscall_table[MUTEX_INIT_NO];
//     syscall_func(mutex);
// }

// int mutex_lock(Mutex_t * mutex){
//     Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
//     Syscall_t syscall_func = (Syscall_t) syscall_table[MUTEX_LOCK_NO];
//     syscall_func(mutex);
// }

// int mutex_unlock(Mutex_t * mutex){
//     Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
//     Syscall_t syscall_func = (Syscall_t) syscall_table[MUTEX_UNLOCK_NO];
//     syscall_func(mutex);
// }
// /**
//  * Initialize the semaphore sem
//  */
// void sem_init(Semaphore_t *sem, int value){
//     Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
//     Syscall_t syscall_func = (Syscall_t) syscall_table[SEM_INIT_NO];
//     syscall_func(sem, value);   
// }
// /**
//  * The semaphore wait function
//  */
// int sem_wait(Semaphore_t *sem){
//     Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
//     Syscall_t syscall_func = (Syscall_t) syscall_table[SEM_WAIT_NO];
//     return (int) syscall_func(sem);   
// }
// /**
//  * The semaphore post/signal function
//  */
// int sem_post(Semaphore_t *sem){
//     Syscall_table_t syscall_table = (Syscall_table_t) SYSCALL_VECTOR;
//     Syscall_t syscall_func = (Syscall_t) syscall_table[SEM_POST_NO];
//     return (int) syscall_func(sem);   
// }