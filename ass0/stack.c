    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "stack.h"
    #include "dll.h"

    typedef struct stack
        {
        DLL *list;
        void (*display)(void *,FILE *);
        void (*free)(void *);
        }STACK;

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
        assert(sizeDLL(items->list) > 0);
        return removeDLL(items->list,0);
        }

    void *peekSTACK(STACK *items){
        assert(sizeDLL(items->list) > 0);
        return getDLL(items->list,0);
        }

    int sizeSTACK(STACK *items){
        return sizeDLL(items->list);
        }

    void displaySTACK(STACK *items,FILE *FP){
        fprintf(FP,"|");
        int i = 0;
        for(i=0; i < sizeDLL(items->list); i++){
            items->display(getDLL(items->list, i), FP);
            if(i < sizeDLL(items->list)-1){
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
