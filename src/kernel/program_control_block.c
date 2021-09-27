#include "program_control_block.h"
#include "../drivers/screen.h"

// array containing list of threads(PCBs)
 PCB arr[PCB_ARR_SIZE];

 // array shows if a certain index of PCB arr is free
int occupied[PCB_ARR_SIZE] = {0,0,0,0,0,0,0,0,0};

int curr_pcb_index = 0;
int kernel_esp, kernel_ebp;

void pthread_init( thread_action main ){
    // save kernel stack pointers TODO: Make sure this works
    asm("movl %%esp, %%eax;"
        "movl %%ebp, %%ebx;"
        : "=a" (kernel_esp), "=b" (kernel_ebp));

    thread_t main_pid;
    pthread_create( &main_pid,  main, (void *) 0);
}

/**
 * Terminates the current thread, and releases any resources
 * that might have been with this thead.
 */
void pthread_exit(){
    // exiting a thread
    for(int i=0; i < 10; i++){
        int index = (curr_pcb_index + i) % PCB_ARR_SIZE;
        if (occupied[index] == 1 && arr[index].process_state == Running){
            arr[index].process_state = Terminated;
            occupied[index] = 1;
            break;
        }
    }

    int found_next = 0;
    // switching to the next thread
    for(int i=0; i < 10; i++){
        int index = (curr_pcb_index + i) % PCB_ARR_SIZE;

        if ( occupied[index] == 1 && arr[index].process_state == Ready){
            curr_pcb_index = (curr_pcb_index + i) % PCB_ARR_SIZE;
            found_next = 1;
            arr[curr_pcb_index].process_state = Running;
            break;
        }
    }
    
    if (found_next == 1){
        // Switch to new program
        
        asm("movl %%eax, %%esp;"
            "movl %%ebx, %%ebp;"
            "leave;"
            "ret;"
            : 
            : "a" (arr[curr_pcb_index].esp), "b" (arr[curr_pcb_index].ebp));
        return;
    } else {
        // Restore kernel stack
        print_attr("\nNo other threads to schedule", GREEN_ON_BLACK);
        asm("movl %%eax, %%esp;"
            "movl %%ebx, %%ebp;"
            "leave;"
            "ret;"
            : 
            : "a" (kernel_esp), "b" (kernel_ebp));
        return;
    }

}

/**
 * Create a new thread.
 */
void pthread_create(thread_t *thread, thread_action action,void * args){
    int return_addr, ebp, esp;

    asm("movl 4(%%ebp), %%eax;"
        "movl %%ebp, %%ebx;"
        "movl %%esp, %%ecx;"
        : "=a" (return_addr), "=b" (ebp), "=c" (esp)
        : );
    for(int i=0; i < 10; i++){
        int index = (curr_pcb_index + i) % PCB_ARR_SIZE;
        if (occupied[index] == 1 && arr[index].process_state == Running){
            arr[index].process_state = Ready;
            arr[index].ebp = ebp;
            arr[index].esp = esp;
            break;
        }
    }
    int t_id = -1;

    // find free slot in the PCB array
    for(int i=0; i < 10; i++){
        if (occupied[i] == 0){
            occupied[i] = 1;
            t_id = i;
            break;
        }
    }
    // edge case for debugging purposes
    if (t_id == -1){
        print_attr("no more space for threads\n", YELLOW_ON_BLUE);
    }

    // create the PCB( program counter block for the new thread)
    PCB new_thread;
    new_thread.process_state = Running;
    new_thread.id = t_id;
    new_thread.ebp = STACK_START + (0x1000 * t_id) ;
    new_thread.esp = new_thread.ebp;// + 0x1000; 

    // sotring it in the PCB array
    arr[t_id] = new_thread;
    
    // storing its id
    *thread = t_id; 

    // Change esp and ebp to thread's ebp and esp
    
    asm("movl %%eax, %%esp;"
        "movl %%ebx, %%ebp;"
        "call %%ecx"
        : 
        : "a" (new_thread.esp), "b" (new_thread.ebp), "c" ((int) action));
    // calling the function the theard suppose to do
    pthread_exit();
}

/**
 * Getting this thread's id
 */
Tid_t gettid(){
    for(int i=0; i < 10; i++){
        int index = (curr_pcb_index + i) % PCB_ARR_SIZE;
        if (occupied[index] == 1 && arr[index].process_state == Running){
            return arr[index].id;
        }
    }
    // indicates there is no running thread, for debuggin purposes
    return -1;
}

/**
 * Getting the process id
 */
Pid_t getpid(){
    return gettid();
}

/**
 * The yield function. Gives up control of cpu.
 */
void pthread_yield(){
    int return_addr, ebp, esp;

    asm("movl 4(%%ebp), %%eax;"
        "movl %%ebp, %%ebx;"
        "movl %%esp, %%ecx;"
        : "=a" (return_addr), "=b" (ebp), "=c" (esp)
        : );

    int thread_id_to_yield;

    for(int i=0; i < 10; i++){
        int index = (curr_pcb_index + i) % PCB_ARR_SIZE;
        if (occupied[index] == 1 && arr[index].process_state == Running){
            arr[index].process_state = Ready;
            thread_id_to_yield = index;
            break;
        }
    }

    // Save the important states of thread
    arr[thread_id_to_yield].esp = esp;
    arr[thread_id_to_yield].ebp = ebp;
    arr[thread_id_to_yield].pc = return_addr;

    for(int i=1; i < 11; i++){
        int index = (thread_id_to_yield + i) % PCB_ARR_SIZE;
        if (occupied[index] == 1 && arr[index].process_state == Ready){
            curr_pcb_index = (thread_id_to_yield + i) % PCB_ARR_SIZE;
            arr[curr_pcb_index].process_state = Running;
            break;
        }
    }

    // Switch to new program
    asm("movl %%eax, %%esp;"
        "movl %%ebx, %%ebp;"
        "leave;"
        "ret;"
        : 
        : "a" (arr[curr_pcb_index].esp), "b" (arr[curr_pcb_index].ebp));
    return;
}
