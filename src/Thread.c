#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <Thread.h>

void InitThread(Thread* thread_t, void (*function_ptr), void* args) {

    pthread_t thread;
    pthread_attr_t thread_attribute;
    pthread_attr_init(&thread_attribute);

    thread_t->thread_id = thread;
    thread_t->attribute = thread_attribute;
    thread_t->threadRunnable = function_ptr;
    thread_t->args = args;

    pthread_create(&thread_t->thread_id, &thread_t->attribute, thread_t->threadRunnable, thread_t->args);
}

void DeInitThread(Thread* thread_t) {
    
    if (pthread_join(thread_t->thread_id, NULL) == EINVAL){
        printf("failed to join thread\n");
    }

    pthread_attr_destroy(&thread_t->attribute);
    thread_t->threadRunnable = NULL;
    thread_t->thread_id = 0;
    free(thread_t);
}