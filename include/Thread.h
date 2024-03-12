#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

typedef struct {
    pthread_t thread_id;
    pthread_attr_t attribute;
    void* (*threadRunnable)();
    void** args;
} Thread;

void InitThread(Thread* thread_t, void (*function_ptr), void* args);

void DeInitThread(Thread* thread_t);


#endif

