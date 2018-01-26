#include <stdio.h>
#include "stack.h"
#include "sll.h"

    struct STACK
	{
	SLL *list;
	void *(display)(void *,FILE *);
	void *(free)(void *);
	};

    STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *)){
	STACK *items = malloc(sizeof(STACK));
	assert(stack != 0);
	items->list = newSLL(d,f);
	stack->display = d;
	stack->free = f;
	return stack;
	}
 
    void push(STACK *items,void *value){
	insertSLL(items->list,0,value); 
	}
    
    void *pop(STACK *items){
	assert(items->list->size > 0);
	return removeSLL(items,0);
	}
    
    void *peekSTACK(STACK *items){
	assert(items->list->size);
	return getSLL(items,0);
	}

    int sizeSTACK(STACK *items){
	return items->list->size;
	}

    void displaySTACK(STACK *items,FILE *FP){
	fprintf(FP,"|");
	
	fprintf(FP,"|");
	}

    void displaySTACKdebug(STACK *items,FILE *FP){
	displaySLLdebug(items->list,FP);
	}

    void freeSTACK(STACK *items){
	freeSLL(items->list);
	free(items);
	}
