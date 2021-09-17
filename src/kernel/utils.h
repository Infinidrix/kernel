
#ifndef KERNEL_UTILS
#define KERNEL_UTILS

void memory_copy(char *source, char *dest, int no_bytes);
char *int_to_string(char * result, unsigned int number);
char *short_to_string(char * result, unsigned short number);
void reverse_string(char * string, int size);
void memset(char *loc, char set_bit, int no_bytes);
/**
 * Some typedefs to make life easier...
 */  
typedef int thread_t;

typedef void * (*thread_action)(void *);
typedef void * (*Syscall_t)(void * arg,...);
typedef void * (*Syscall_noarg_t)();

typedef Syscall_t * Syscall_table_t;
typedef int Tid_t;
typedef int Pid_t;

/**
 * This is the syscall table, where the system call
 * handlers reside in memory.
 */
#define SYSCALL_VECTOR  0x02100000
#define MAX_ENTRIES 128


/** 
 * The syscalls and their indexes within the system call vector/table.
*/
#define LOADER_NO           0
#define PRINTLN_NO          1 
#define PRINT_INT_NO        2
#define THREAD_CREATE_NO    3
#define THREAD_EXIT_NO      4     
#define GET_TID_NO          5
#define GET_PID_NO          6
#define THREAD_YIELD_NO     7
#define MUTEX_LOCK_NO       8
#define MUTEX_UNLOCK_NO     9
#define MUTEX_INIT_NO       10
#define SEM_INIT_NO         11
#define SEM_WAIT_NO         12
#define SEM_POST_NO         13

/**
 * Below are the library wrapper functions, not the actually system call handlers/ implementations.
 */
/**
 * Print the string str using its attribute atrr
 */
void print_syscall(char * str, char atrr);
/**
 * Print an integer
 */
void print_int_syscall(int num, char attr);
/**
 * Terminates the current thread, and releases any resources
 * that might have been with this thead.
 */
void pthread_exit();

/**
 * Create a new thread.
 */
void pthread_create(thread_t *thread, thread_action action,void * args);

/**
 * Getting this thread's id
 */
Tid_t gettid();

/**
 * Getting the process id
 */
Pid_t getpid();

/**
 * The yield function. Gives up control of cpu.
 */
void pthread_yield();

#endif
