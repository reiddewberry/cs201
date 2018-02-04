    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "sll.h"

    typedef struct node
        {
        void *data;
        struct node *next;
        }NODE;

/*
    NODE *newNODE(void *value,NODE *next){
        NODE *p = malloc(sizeof(NODE));
        assert(p != 0);
        p->data = value;
        p->next = next;
        return p;
        }
*/

    //The Single Linked List structure
    typedef struct sll
        {
        NODE *head;
        NODE *tail;
        int size;
        void (*display)(void *,FILE *);
        void (*free)(void *);
        }SLL;

    //Creates a new Sinle Linked List
    SLL *newSLL(void (*d)(void *value,FILE *FP),void (*f)(void *value))
        {
        SLL *items = malloc(sizeof(SLL));
        assert(items != 0);
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->display = d;
        items->free = f;
        return items;
        }

    //Inserts nodes into the SLL
    void insertSLL(SLL *items,int index,void *value){
        assert(index >= 0 && index <= items->size);
        NODE *new = malloc(sizeof(NODE));
        new->data = value;
        new->next = 0;
        if (index == 0){
            new->next = items->head;
            items->head = new;
            if(items->size == 0){
                items->tail = new;
                }
            items->size += 1;
            return;
            }
        else if(index == items->size){
            items->tail->next = new;
            items->tail = new;
            new->next = 0;
            items->size += 1;
            return;
            }
        else{
            NODE *tempnode = items->head;
            new->next = items->head;
            int i = 0;
            for (i=0; i < index; i++){
                new->next = new->next->next;
                if(i < index-1){
                    tempnode = tempnode->next;
                    }
                }
               tempnode->next = new;
            items->size += 1;
            }
        }

    //Removes a certain node from the list
    void *removeSLL(SLL *items,int index){
        assert(items->size > 0 && index >= 0 && index < items->size);
        NODE *tempNode = items->head;
        NODE *removeNode = items->head;
        int i = 0;
        for(i=0; i < index; i++){
            removeNode = removeNode->next;
            if(i < index-1){
                tempNode = tempNode->next;
                }
            }
        if(removeNode == items->head){
            void *removeVal = removeNode->data;
            if(items->size == 1){
                items->head = 0;
                items->tail = 0;
                items->size -= 1;
                free(removeNode);
                return removeVal;
                }
            items->head = removeNode->next;
            free(removeNode);
            items->size -= 1;
            return removeVal;
            }
        void *removeVal = removeNode->data;
        if(removeNode == items->tail){
            items->tail = tempNode;
            tempNode->next = 0;
            }
        else{
            tempNode->next = removeNode->next;
            }
        free(removeNode);
        items->size -= 1;
        return removeVal;
        }

    //Combines 2 lists  items, index, value
    void unionSLL(SLL *recipient,SLL *donor){
        if(donor->tail != 0){
            if(recipient->head != 0){
                recipient->tail->next = donor->head;
                }
            else{
                recipient->head = donor->head;
                }
            recipient->tail = donor->tail;
            }
        recipient->size += donor->size;
        donor->head = 0;
        donor->tail = 0;
        donor->size = 0;
        }

    //Gives you the value of the Node at a given index
    void *getSLL(SLL *items,int index){
        assert(index >= 0 && index < items->size);
        if(index == items->size-1){
            return items->tail->data;
            }
        NODE *tempNode = items->head;
        int i = 0;
        for(i=0; i < index; i++){
            tempNode = tempNode->next;
            }
        return tempNode->data;
        }

    //Finds, gives, and updates the value for the Node at the given index
    void *setSLL(SLL *items,int index,void *value){
        assert(index >= 0 && index <= items->size);
        if(index == items->size){
            insertSLL(items, index, value);
            return 0;
            }
        int i = 0;
        if(index == items->size-1){
            void *returnVal = items->tail->data;
            items->tail->data = value;
            return returnVal;
            }
        NODE *tempNode = items->head;
        for(i=0; i < index; i++){
            tempNode = tempNode->next;
            }
        void *returnVal = tempNode->data;
        tempNode->data = value;
        return returnVal;
        }

    //returns the size of the SLL
    int sizeSLL(SLL *items){
        return items->size;
        }

    //displays the SLL as values in a list e.g. {5,6,2,9,1} or {}
    void displaySLL(SLL *items,FILE *FP){
        fprintf(FP,"{");
        NODE *printNode = items->head;
        while(printNode != 0){
            items->display(printNode->data,FP);
            printNode = printNode->next;
            if(printNode != 0){
                fprintf(FP,",");
                }
            }
        fprintf(FP,"}");
        }

    //displays a SLL with more e.g.(SLL:  3,1,2) "head->{3,1,2},tail->{2}"
    void displaySLLdebug(SLL *items,FILE *FP){
        fprintf(FP,"head->");
        displaySLL(items,FP);
        NODE *tailNode = items->head;
        fprintf(FP,",tail->");
        if(tailNode != 0){
            fprintf(FP,"{");
            items->display(items->tail->data,FP);
            fprintf(FP,"}");
            }
        else{fprintf(FP,"{}");}
        }

    //walks through the SLL and frees nodes with the freeing function
    void freeSLL(SLL *items){
        NODE *freeNode = items->head;
        NODE *nextNode = items->head;
        while(freeNode != 0){
            if(items->free != 0){
                items->free(freeNode->data);
                }
            if(nextNode != 0){
                nextNode = nextNode->next;
                }
            free(freeNode);
            freeNode = nextNode;
            }
        free(items);
        }
