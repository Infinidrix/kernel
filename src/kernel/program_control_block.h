// states
enum state {Ready, Running, Terminated};

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
