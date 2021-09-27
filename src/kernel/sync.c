#include "sync.h"

void mutex_init(Mutex_t *lock){
    *lock = 1;
}

void mutex_lock(Mutex_t *lock){
    while (*lock == 0){
        // pthread_yield();
    }
    *lock = 0;
}

void mutex_unlock(Mutex_t *lock){
    *lock = 1;
}

void semaphore_init(Semaphore_t *lock){
    *lock = 0;
}

void semaphore_wait(Semaphore_t *lock){
    while (*lock <= 0){
        //pthread_yield();
    }
    *lock--;
}

void semaphore_post(Semaphore_t *lock){
    *lock++;
}