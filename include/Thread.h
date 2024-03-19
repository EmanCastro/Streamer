#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

typedef struct {
    pthread_t thread_id;
    pthread_attr_t attribute;
    void* (*threadRunnable)();
    void** args;
} Thread;

/**
 * @brief Initializes a custom Thread, pass a runnable function to be executed and its args
 * 
 * @param thread_t 
 * @param args 
 */
void InitThread(Thread* thread_t, void (*function_ptr), void* args);

/**
 * @brief Deinitializes a custom Thraed
 * 
 * @param thread_t 
 */
void DeInitThread(Thread* thread_t);


#endif

