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
	insertSLL(items->list, 0, value); 
	}
    
    void *pop(STACK *items){
	removeSLL();
	}
    
    void *peekSTACK(STACK *items);
    int sizeSTACK(STACK *items);
    void displaySTACK(STACK *items,FILE *);
    void displaySTACKdebug(STACK *items,FILE *);
    void freeSTACK(STACK *items);
