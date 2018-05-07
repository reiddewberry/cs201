/*
Chandler Reid Dewberry
Queue Program
*/
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "queue.h"
    #include "sll.h"

//QUEUE structure
    typedef struct queue
        {
        SLL *list;                      //pointer to underlying Singly-linked List struct
        void (*display)(void *,FILE *); //passed in display function
        void (*free)(void *);           //passed in free function
        }QUEUE;

/*
Public Function to create and initialize a new QUEUE
Parameters:
    *d - Display function to display whatever is stored in the QUEUE
    *f - Frees whatever is stored in the QUEUE
*/
    QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *)){
        //malloc to allocate memory and assert to verify there is enough
        QUEUE *items = malloc(sizeof(QUEUE));
        assert(items != 0);
        //create and initilize the SLL
        items->list = newSLL(d,f);
        items->display = d;
        items->free = f;
        return items;
        }

//Inserts the passed in value into the back of the SLL
    void enqueue(QUEUE *items,void *value){
        insertSLL(items->list,sizeSLL(items->list),value);
        }

//Removes and Returns what is at the front of the SSL
    void *dequeue(QUEUE *items){
        //assert to verify the list isn't empty and the program is working
        assert(sizeSLL(items->list) > 0);
        return removeSLL(items->list,0);
        }

//Doesn't Remove but Returns the pointer to what is at the front of the SLL
    void *peekQUEUE(QUEUE *items){
        assert(sizeSLL(items->list) > 0);
        return getSLL(items->list,0);
        }

//Returns the # of items in the QUEUE
    int sizeQUEUE(QUEUE *items){
        return sizeSLL(items->list);
        }

/*
Prints the Queue in order
2 Parameters:
    items - the QUEUE to be displayed
    fp - file pointer to print to
ex.
<3,5,2,7>
*/
    void displayQUEUE(QUEUE *items,FILE *FP){
        fprintf(FP,"<");
        int i = 0;
        //iterates throught the SLL by the index #
        for(i=0; i < sizeSLL(items->list); i++){
            items->display(getSLL(items->list,i),FP);
            if(i < sizeSLL(items->list)-1){
                fprintf(FP,",");
                }
            }
        fprintf(FP,">");
        }

//Prints the Queue but with more info
//ex. "head->{3,5,2,7},tail->{7}"
    void displayQUEUEdebug(QUEUE *items,FILE *FP){
        displaySLLdebug(items->list,FP);
        }

/*
Frees: 
    QUEUE
    Underlying SLL
    Data - if a Freeing function was passed in
*/
    void freeQUEUE(QUEUE *items){
        freeSLL(items->list);
        free(items);
        }
