    #ifndef __QUEUE_INCLUDED__
    #define __QUEUE_INCLUDED__

    #include <stdio.h>
    #include "dll.h"

    typedef struct queue QUEUE;

    QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *)); 
    
    void enqueue(QUEUE *items,void *value);
    
    void *dequeue(QUEUE *items);
    
    void *peekQUEUE(QUEUE *items);
    
    int sizeQUEUE(QUEUE *items);

    void displayQUEUE(QUEUE *items,FILE *);
    
    void displayQUEUEdebug(QUEUE *items,FILE *);
    
    void freeQUEUE(QUEUE *items);

    #endif
