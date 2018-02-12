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

    void insertHEAP(HEAP *heap,void *value){
        BSTNODE *newNode = malloc(sizeof(BSTNODE));
        setBSTNODEvalue(newNode,value);
        enqueue(heap->queue,newNode);
        if(getBSTroot(heap->tree) == 0){
            setBSTroot(heap->tree,newNode);
            }
        else{
            BSTNODE *checkNode = peekQUEUE(heap->queue);
            setBSTNODEparent(newNode,checkNode);
            if(getBSTNODEleft(checkNode) == 0){
                setBSTNODEleft(checkNode,newNode);
                }
            else{
                setBSTNODEright(checkNode,newNode);
                dequeue(heap->queue);
                }
            }
        push(heap->stack,newNode);
        heap->size += 1;
        }

    //creates the max or min heap by heapify. (bubble down)
    void buildHEAP(HEAP *heap){
        
        }

    //returns the value at the root
    void *peekHEAP(HEAP *heap){
        return getBSTNODEvalue(getBSTroot(heap->tree));
        }

    void *extractHEAP(HEAP *heap){
        BSTNODE *newRoot = pop(heap->stack);
        void *rootVal = getBSTNODEvalue(getBSTroot(heap->tree));
        setBSTNODEvalue(getBSTroot(heap->tree),getBSTNODEvalue(newRoot));
        setBSTNODEparent(newRoot,0);
        return rootVal;
        }

    int  sizeHEAP(HEAP *heap){
        return sizeBST(heap->tree);
        }

    void displayHEAP(HEAP *heap,FILE *fp){
        displayBST(heap->tree,fp);
        }

    void displayHEAPdebug(HEAP *heap,FILE *fp){
        fprintf(fp,"heap size: %d\n",heap->size;
        fprintf(fp,"bst size: %d\n",sizeBST(heap->tree));
        displayBSTdebug(heap->tree,fp);
        }

    void freeHEAP(HEAP *heap){
        freeBST(heap->tree);
        freeQUEUE(heap->queue);
        freeSTACK(heap->stack);
        }
