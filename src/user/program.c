#include "../stdlib/stdlib.h"

int x =0;
Mutex_t mutex;
void * action(void * args){
    Tid_t tid = gettid();
    pthread_yield();    
    // mutex_lock(&mutex);
    print_syscall("** Thread Id : ", WHITE_ON_BLACK);
    print_int_syscall( tid, WHITE_ON_BLACK);
    print_syscall("** x :  ",WHITE_ON_BLACK);
    print_int_syscall(++x, WHITE_ON_BLACK);
    // mutex_unlock(&mutex);    
}
void * action2(void * args){
    // mutex_lock(&mutex);
    pthread_yield();    
    Tid_t tid = gettid();    
    print_syscall("** Thread Id : ", WHITE_ON_BLACK);
    print_int_syscall( tid, WHITE_ON_BLACK);
    print_syscall("** x :  ",WHITE_ON_BLACK);
    print_int_syscall(++x, WHITE_ON_BLACK);
    // mutex_unlock(&mutex);    
}
int main(){ 
    Pid_t pid = getpid();    
    print_int_syscall(x, BLACK_ON_WHITE);
    print_syscall(" ** main thread. pid : \n",YELLOW_ON_BLUE);   
    print_int_syscall(pid, WHITE_ON_BLACK);   
    mutex_init(&mutex);
    thread_t thread,t2,t3,t4,t5,t6,t7;
    pthread_create(&thread, action , 0);
    pthread_create(&t2, action , 0);

    pthread_create(&t3, action , 0);
    pthread_create(&t4, action2 , 0);
    pthread_create(&t5, action2 , 0);
    pthread_create(&t6, action2 , 0);
     
    return 0;
}
