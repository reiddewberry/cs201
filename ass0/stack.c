    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "stack.h"
    #include "sll.h"

    typedef struct stack STACK;

    struct STACK
        {
        DLL *list;
        void *(display)(void *,FILE *);
        void *(free)(void *);
        };

    STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *)){
        STACK *items = malloc(sizeof(STACK));
        assert(items != 0);
        items->list = newDLL(d,f);
        items->display = d;
        items->free = f;
        return items;
        }

    void push(STACK *items,void *value){
        insertDLL(items->list,0,value);
        }

    void *pop(STACK *items){
        assert(items->list->size > 0);
        return removeDLL(items->list,0);
        }

    void *peekSTACK(STACK *items){
        assert(items->list->size);
        return getDLL(items->list,0);
        }

    int sizeSTACK(STACK *items){
        return items->list->size;
        }

    void displaySTACK(STACK *items,FILE *FP){
        fprintf(FP,"|");
        int i = 0;
        for(i=0; i < items->list->size; i++){
            fprintf(FP,getDLL(items->list,i));
            if(i < items->list->size-1){
                fprintf(FP,",");
                }
            }
        fprintf(FP,"|");
        }

    void displaySTACKdebug(STACK *items,FILE *FP){
        displayDLLdebug(items->list,FP);
        }

    void freeSTACK(STACK *items){
        freeDLL(items->list);
        free(items);
        }
