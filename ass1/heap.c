    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "stack.h"
    #include "queue.h"
    #include "bst.h"


    typedef struct heap{
        int size;
        BST *tree;
        QUEUE *queue;
        STACK *stack;
        void (*display)(void *,FILE *);
        int (*compare)(void *, void *);
        void (*free)(void *);
        }HEAP;



    HEAP *newHEAP(
        void (*d)(void *,FILE *),    //display
        int (*c)(void *,void *),     //compare
        void (*f)(void *)){          //free
        HEAP *heap = malloc(sizeof(HEAP));
        heap->size = 0;
        heap->tree = newBST(d,0,0,f);
        heap->queue = newQUEUE(0,0);
        heap->stack = newSTACK(0,0);
        heap->display = d;
        heap->compare = c;
        heap->free = f;
        return heap
        }

    void insertHEAP(HEAP *h,void *value){
        
        }

    void buildHEAP(HEAP *h);
    void *peekHEAP(HEAP *h);
    void *extractHEAP(HEAP *h);
    int  sizeHEAP(HEAP *h);
    void displayHEAP(HEAP *h,FILE *fp);
    void displayHEAPdebug(HEAP *h);
    void freeHEAP(HEAP *h);
