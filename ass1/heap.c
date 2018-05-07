/*
Chandler Reid Dewberry
Heap Program
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "queue.h"
#include "bst.h"

//heap structure
    typedef struct heap{
        int size;                       //int value of how many nodes are in the heap
        BST *tree;                      //underlying BST structure
        QUEUE *queue;                   //underlying QUEUE structure
        STACK *stack;                   //underlying STACK structure
        void (*display)(void *,FILE *); //display function passed in
        int (*compare)(void *, void *); //compare function passed in
        void (*free)(void *);           //free function passed in
        }HEAP;

//Public function to create and initialize a new HEAP
    HEAP *newHEAP(
        void (*d)(void *,FILE *),    //display
        int (*c)(void *,void *),     //compare
        void (*f)(void *)){          //free
        //malloc is used to allocate memory and assert to verify there is enough
        HEAP *heap = malloc(sizeof(HEAP));
        assert(heap != 0);
        heap->size = 0;
        heap->tree = newBST(d,0,0,f);
        heap->queue = newQUEUE(0,0);
        heap->stack = newSTACK(0,0);
        heap->display = d;
        heap->compare = c;
        heap->free = f;
        return heap;
        }
/*
Inserts a value into the HEAP
2 Parameters:
    heap - the HEAP that will be inserted into
    value - whatever data the user  is inserting into the heap
*/
    void insertHEAP(HEAP *heap,void *value){
        //create the new Node and verify it exists
        BSTNODE *newNode = newBSTNODE(value);
        assert(newNode != 0);
        //enqueue the new Node to the QUEUE
        enqueue(heap->queue,newNode);
        //if the HEAP is empty, set the Node as the Root
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
        //pushes the Node onto the STACK
        push(heap->stack,newNode);
        //increases the HEAP size and the BST size
        heap->size += 1;
        setBSTsize(heap->tree,(sizeBST(heap->tree)+1));
        }

    static void bubbleDown(HEAP *heap,BSTNODE *bubbleNode){
        BSTNODE *leftChild = getBSTNODEleft(bubbleNode);
        BSTNODE *rightChild = getBSTNODEright(bubbleNode);
        if(leftChild == 0 && rightChild == 0){
            return;
            }
        int compLeft = 0;
        int compRight = 0;
        if(rightChild == 0){
            compLeft = heap->compare( getBSTNODEvalue(bubbleNode) , getBSTNODEvalue(leftChild) );
            compRight = 0;
            }
        else{
            compLeft = heap->compare( getBSTNODEvalue(bubbleNode) , getBSTNODEvalue(leftChild) );
            compRight = heap->compare( getBSTNODEvalue(bubbleNode) , getBSTNODEvalue(rightChild) );
            }
        while(compLeft > 0 || compRight > 0){
            if(rightChild == 0){
                if(compLeft > 0){
                    void *tempVal = getBSTNODEvalue(bubbleNode);
                    setBSTNODEvalue(bubbleNode,getBSTNODEvalue(leftChild));
                    setBSTNODEvalue(leftChild,tempVal);
                    bubbleNode = leftChild;
                    }
                }
            else{
                if(heap->compare(getBSTNODEvalue(leftChild),getBSTNODEvalue(rightChild)) < 0){
                    void *tempVal = getBSTNODEvalue(bubbleNode);
                    setBSTNODEvalue(bubbleNode,getBSTNODEvalue(leftChild));
                    setBSTNODEvalue(leftChild,tempVal);
                    bubbleNode = leftChild;
                    }
                else{
                    void *tempVal = getBSTNODEvalue(bubbleNode);
                    setBSTNODEvalue(bubbleNode,getBSTNODEvalue(rightChild));
                    setBSTNODEvalue(rightChild,tempVal);
                    bubbleNode = rightChild;
                    }
            }
            leftChild = getBSTNODEleft(bubbleNode);
            rightChild = getBSTNODEright(bubbleNode);
            if(leftChild == 0){
                break;
                }
            if(rightChild == 0){
                compLeft = heap->compare( getBSTNODEvalue(bubbleNode) , getBSTNODEvalue(leftChild) );
                compRight = 0;
                }
            else{
                compLeft = heap->compare( getBSTNODEvalue(bubbleNode) , getBSTNODEvalue(leftChild) );
                compRight = heap->compare( getBSTNODEvalue(bubbleNode) , getBSTNODEvalue(rightChild) );
                }
            }
        }

/*
Creates the max or min heap by heapify. (bubble down)
IMPORTANT: Extract Heap cannot be called after this
1 Parameter:
    heap - HEAP to be heapified
*/
    void buildHEAP(HEAP *heap){
        //free the QUEUE
        freeQUEUE(heap->queue);
        //make a new QUEUE
        heap->queue = newQUEUE(0,0);
        //Goes through each Node and bubbles them down.
        for(int i=0;i < heap->size; i++){
            BSTNODE *heapifyNode = pop(heap->stack);
            enqueue(heap->queue,heapifyNode);
            bubbleDown(heap,heapifyNode);
            }
        }

    //returns the value at the root
    void *peekHEAP(HEAP *heap){
        return getBSTNODEvalue(getBSTroot(heap->tree));
        }

/*
Switches the farthest right leaf with the root
and frees the value. Then bubbles the new root down
1 Parameter:
    heap - the HEAP that you are extracting from
Returns:
    The current Minimum or Maximum depending on the type of Heap
*/
    void *extractHEAP(HEAP *heap){
        BSTNODE *newRoot = dequeue(heap->queue);
        BSTNODE *heapRoot = getBSTroot(heap->tree);
        void *rootVal = getBSTNODEvalue(heapRoot);
        setBSTNODEvalue(heapRoot,getBSTNODEvalue(newRoot));
        if(getBSTNODEparent(newRoot) == 0){
            setBSTsize(heap->tree,0);
            setBSTroot(heap->tree,0);
            heap->size -= 1;
            return rootVal;
            }
        pruneLeafBST(heap->tree,newRoot);
        free(newRoot);
        bubbleDown(heap,heapRoot);
        setBSTsize(heap->tree,sizeBST(heap->tree)-1);
        heap->size -= 1;
        return rootVal;
        }

    int  sizeHEAP(HEAP *heap){
        return heap->size;
        }

    void displayHEAP(HEAP *heap,FILE *fp){
        displayBST(heap->tree,fp);
        }

    void displayHEAPdebug(HEAP *heap,FILE *fp){
        fprintf(fp,"heap size: %d\n",heap->size);
        fprintf(fp,"bst size: %d\n",sizeBST(heap->tree));
        displayBSTdebug(heap->tree,fp);
        }

    void freeHEAP(HEAP *heap){
        freeBST(heap->tree);
        freeQUEUE(heap->queue);
        freeSTACK(heap->stack);
        free(heap);
        }
