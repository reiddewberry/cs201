    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "queue.h"
    #include "sll.h"

    typedef struct queue
        {
        SLL *list;
        void (*display)(void *,FILE *);
        void (*free)(void *);
        }QUEUE;

    QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *)){
        QUEUE *items = malloc(sizeof(QUEUE));
        assert(items != 0);
        items->list = newSLL(d,f);
        items->display = d;
        items->free = f;
        return items;
        }

    void enqueue(QUEUE *items,void *value){
        insertSLL(items->list,sizeSLL(items->list),value);
        }

    void *dequeue(QUEUE *items){
        assert(sizeSLL(items->list) > 0);
        return removeSLL(items->list,0);
        }

    void *peekQUEUE(QUEUE *items){
        assert(sizeSLL(items->list) > 0);
        return getSLL(items->list,0);
        }

    int sizeQUEUE(QUEUE *items){
        return sizeSLL(items->list);
        }

    void displayQUEUE(QUEUE *items,FILE *FP){
        fprintf(FP,"<");
        int i = 0;
        for(i=0; i < sizeSLL(items->list); i++){
            items->display(getSLL(items->list,i),FP);
            if(i < sizeSLL(items->list)-1){
                fprintf(FP,",");
                }
            }
        fprintf(FP,">");
        }

    void displayQUEUEdebug(QUEUE *items,FILE *FP){
        displaySLLdebug(items->list,FP);
        }

    void freeQUEUE(QUEUE *items){
        freeSLL(items->list);
        free(items);
        }
