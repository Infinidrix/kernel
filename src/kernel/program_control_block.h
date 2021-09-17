// states
enum state {New, Ready, Running, Wait, Terminated};

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