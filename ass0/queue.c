    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "queue.h"
    #include "dll.h"

    typedef struct queue QUEUE;

    struct QUEUE
        {
        SLL *list;
        void *(display)(void *,FILE *);
        void *(free)(void *);
        };

    QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *)){
        QUEUE *items = malloc(sizeof(QUEUE));
        assert(items != 0);
        items->list = newSLL(d,f);
        items->display = d;
        items->free = f;
        return items;
        }

    void enqueue(QUEUE *items,void *value){
        insertSLL(items->list,items->list->size,value);
        }

    void *dequeue(QUEUE *items){
        assert(items->list->size > 0);
        return removeSLL(items->list,0);
        }

    void *peekQUEUE(QUEUE *items){
        assert(items->list->size > 0);
        return getSLL(items->list,0);
        }

    int sizeQUEUE(QUEUE *items){
        return items->list->size;
        }

    void displayQUEUE(QUEUE *items,FILE *FP){
        fprintf(FP,"<")
        int i = 0;
        for(i=0; i < items->list->size; i++){
            fprintf(FP,getSLL(items->list,i));
            if(i < items->list->size-1){
                fprintf(FP,",")
                }
            }
        fprintf(FP,">")
        }

    void displayQUEUEdebug(QUEUE *items,FILE *FP){
        displaySLLdebug(items->list,FP);
        }

    void freeQUEUE(QUEUE *items){
        freeSLL(items->list);
        free(items);
        }
