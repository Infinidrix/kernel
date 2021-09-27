
#ifndef SYNC_H
#define SYNC_H 1
typedef int Mutex_t;
typedef int Semaphore_t;
void mutex_init(Mutex_t *lock);

void mutex_lock(Mutex_t *lock);

void mutex_unlock(Mutex_t *lock);

void semaphore_init(Semaphore_t *lock);

void semaphore_wait(Semaphore_t *lock);

void semaphore_post(Semaphore_t *lock);

#endif