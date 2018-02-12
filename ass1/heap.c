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

    void insertHEAP(HEAP *heap,void *value){
        BSTNODE *newNode = newBSTNODE(value);
        assert(newNode != 0);
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
            }
        else{
            compRight = heap->compare( getBSTNODEvalue(bubbleNode) , getBSTNODEvalue(rightChild) );
            }
        while(compLeft > 0 || compRight > 0){
            if(rightChild == 0){
                if(compLeft > 0){
                    void *tempVal = getBSTNODEvalue(bubbleNode);
                    setBSTNODEvalue(bubbleNode,getBSTNODEvalue(leftChild));
                    setBSTNODEvalue(leftChild,tempVal);
                    bubbleNode = getBSTNODEleft(bubbleNode);
                    }
                }
            else{
                if(heap->compare(getBSTNODEvalue(leftChild),getBSTNODEvalue(rightChild)) < 0){
                    void *tempVal = getBSTNODEvalue(bubbleNode);
                    setBSTNODEvalue(bubbleNode,getBSTNODEvalue(leftChild));
                    setBSTNODEvalue(leftChild,tempVal);
                    bubbleNode = getBSTNODEleft(bubbleNode);
                    }
                else{
                    void *tempVal = getBSTNODEvalue(bubbleNode);
                    setBSTNODEvalue(bubbleNode,getBSTNODEvalue(rightChild));
                    setBSTNODEvalue(rightChild,tempVal);
                    bubbleNode = getBSTNODEright(bubbleNode);
                    }
            }
            leftChild = getBSTNODEleft(bubbleNode);
            rightChild = getBSTNODEright(bubbleNode);
            if(leftChild == 0){
                break;
                }
            if(rightChild == 0){
                heap->compare( getBSTNODEvalue(bubbleNode) , getBSTNODEvalue(leftChild) );
                }
            else{
                heap->compare( getBSTNODEvalue(bubbleNode) , getBSTNODEvalue(leftChild) );
                heap->compare( getBSTNODEvalue(bubbleNode) , getBSTNODEvalue(rightChild) );
                }
            }
        }

    //creates the max or min heap by heapify. (bubble down)
    void buildHEAP(HEAP *heap){
        int i = 0;
        freeQUEUE(heap->queue);
        heap->queue = newQUEUE(0,0);
        for(i=0;i < heap->size; i++){
            BSTNODE *heapifyNode = pop(heap->stack);
            enqueue(heap->queue,heapifyNode);
            bubbleDown(heap,heapifyNode);
            }
        }

    //returns the value at the root
    void *peekHEAP(HEAP *heap){
        return getBSTNODEvalue(getBSTroot(heap->tree));
        }

    //switches the farthest right leaf with the root
    //and frees the value. Then bubbles the new root down
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
        if(getBSTNODEleft(getBSTNODEparent(newRoot)) == newRoot){
            setBSTNODEleft(getBSTNODEparent(newRoot),0);
            }
        else{
            setBSTNODEright(getBSTNODEparent(newRoot),0);
            }
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
