#include "program_control_block.h"
#include "../drivers/screen.h"

// array containing list of threads(PCBs)
 PCB arr[10];

 // array array showns if a certain index of PCB arr is free
int occupied[10] = {0,0,0,0,0,0,0,0,0};

/**
 * Terminates the current thread, and releases any resources
 * that might have been with this thead.
 */
void pthread_exit(){
    // exiting a thread
    for(int i=0; i < 10; i++){
        if (arr[i].process_state == Running){
            arr[i].process_state == Terminated;
            occupied[i] = 0;
            break;
        }
    }
}

/**
 * Create a new thread.
 */
void pthread_create(thread_t *thread, thread_action action,void * args){
    int t_id = -1;

    // the start0x05048000

    // find free slot in the PCB array
    for(int i=0; i < 10; i++){
        if (occupied[i] == 0){
            occupied[i] == 1;
            t_id = i;
            break;
        }
    }

    // edge case for debugging purposes
    if (t_id == -1){
        print("no more space for threads");
    }

    // create the PCB( program counter block for the new thread)
    PCB new_thread;
    new_thread.process_state = Ready;
    new_thread.id = t_id;
    new_thread.esp = 0x05048000;
    new_thread.ebp = 0x05047000;

    new_thread.eax = 0x0;
    new_thread.ebx = 0x0;
    new_thread.ebx = 0x0;
    new_thread.ecx = 0x0;
    new_thread.edx = 0x0;

    // sotring it in the PCB array
    arr[t_id] = new_thread;
    
    // stroing its id
    *thread = t_id; 

    // calling the function the theard suppose to do
    action((void *) 0);

    // the 'action' function returns the control  
    pthread_exit();
}

/**
 * Getting this thread's id
 */
Tid_t gettid(){
    for(int i=0; i < 10; i++){
        if (arr[i].process_state == Running){
            return arr[i].id;
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
    for(int i=0; i < 10; i++){
        if (arr[i].process_state == Running){
            arr[i].process_state == Wait;
            break;
        }

    }

    for(int i=0; i < 10; i++){
        if (arr[i].process_state == Wait){
            arr[i].process_state == Running;
            break;
        }
    }
}
