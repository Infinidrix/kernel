// states
enum state {Ready, Running, Terminated};

#define STACK_START 0x05048000
#define PCB_ARR_SIZE 10

typedef struct {
    // process state
    enum state process_state;

    //process id
    int id;

    //program counter
    int pc;

    //registers
    int eax;
    int ecx;
    int edx;
    int ebx;
    int esi;
    int edi;
    int esp;
    int ebp;
} PCB ;

typedef int thread_t;
typedef int Mutex_t;
typedef int Semaphore_t;

typedef void * (*thread_action)(void *);

typedef int Tid_t;
typedef int Pid_t;

void pthread_init( thread_action main );

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