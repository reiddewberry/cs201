    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "dll.h"

    typedef struct node
        {
        void *data;
        struct node *prev;
        struct node *next;
        }NODE;

    typedef struct dll
        {
        NODE *head;
        NODE *tail;
        int size;
        void (*display)(void *,FILE *);
        void (*free)(void *);
        }DLL;


    DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *))
        {
        DLL *items = malloc(sizeof(DLL));
        assert(items != 0);
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->display = d;
        items->free = f;
        return items;
        }

    //inserts a new node with value into the DLL
    void insertDLL(DLL *items,int index,void *value){
        assert(index >= 0 && index <= items->size);
        NODE *newNode = malloc(sizeof(NODE));
        newNode->data = value;
        newNode->prev = 0;
        newNode->next = 0;
        //If its the head, set everything
        if(index == 0){
            newNode->prev = 0;
            newNode->next = items->head;
            if(items->size == 0){
                items->head = newNode;
                items->tail = newNode;
                items->size += 1;
                return;
                }
            items->head->prev = newNode;
            items->head = newNode;
            items->size += 1;
            return;
            }
        //If its the tail
        else if(index == items->size){
            items->tail->next = newNode;
            newNode->prev = items->tail;
            items->tail = newNode;
            items->size += 1;
            return;
            }
        //In between
        else{
            if(index < items->size/2){
                int i = 0;
                NODE *tempNode = items->head;
                for(i=0; i < index; i++){
                    tempNode = tempNode->next;
                    }
                newNode->next = tempNode;
                newNode->prev = tempNode->prev;
                tempNode->prev->next = newNode;
                tempNode->prev = newNode;
                items->size += 1;
                }
            else{
                int i = items->size-1;
                NODE *tempNode = items->tail;
                for(i=items->size-1; i > index; i--){
                    tempNode = tempNode->prev;
                    }
                newNode->next = tempNode;
                newNode->prev = tempNode->prev;
                tempNode->prev->next = newNode;
                tempNode->prev = newNode;
                items->size += 1;
                }
            }
        }

    //removes a certain node in the DLL and returns the value
    void *removeDLL(DLL *items,int index){
        assert(items->size > 0 && index >= 0 && index < items->size);
        NODE *removeNode = items->head;
        if(index < items->size/2){
            int i = 0;
            for(i=0; i < index; i++){
                removeNode = removeNode->next;
                }
            }
        else{
            removeNode = items->tail;
            int i = items->size-1;
            for(i=items->size-1; i > index; i--){
                removeNode = removeNode->prev;
                }
            }
        void *removeVal = removeNode->data;
        if(removeNode == items->head){
            if(items->size == 1){
                items->head = 0;
                items->tail = 0;
                items->size -= 1;
                free(removeNode);
                return removeVal;
                }
            items->head = removeNode->next;
            items->head->prev = 0;
            items->size -= 1;
            free(removeNode);
            return removeVal;
            }
        if(removeNode == items->tail){
            items->tail = removeNode->prev;
            items->tail->next = 0;
            }
        else{
            NODE *prevNode = removeNode->prev;
            prevNode->next = removeNode->next;
            removeNode->next->prev = prevNode;
            }
        free(removeNode);
        items->size -= 1;
        return removeVal;
        }

    //combines 2 DLLs together
    void unionDLL(DLL *recipient,DLL *donor){
        if(donor->tail != 0){
            if(recipient->head == 0){
                recipient->head = donor->head;
                }
            else{
                recipient->tail->next = donor->head;
                donor->head->prev = recipient->tail;
                }
            recipient->tail = donor->tail;
            }
        recipient->size += donor->size;
        donor->head = 0;
        donor->tail = 0;
        donor->size = 0;
        }

    //returns the value at a given index in the DLL
    void *getDLL(DLL *items,int index){
        assert(index >= 0 && index < items->size);
        if(index == items->size-1){
            return items->tail->data;
            }
        if(index < items->size/2){
            NODE *tempNode = items->head;
            int i = 0;
            for(i=0; i < index; i++){
                tempNode = tempNode->next;
                }
            return tempNode->data;
            }
        else{
            NODE *tempNode = items->tail;
            int i = items->size-1;
            for(i=items->size-1; i > index; i--){
                tempNode = tempNode->prev;
                }
            return tempNode->data;
            }
        }

    //sets the value and returns what used to be there. or create a new node at the end
    void *setDLL(DLL *items,int index,void *value){ 
        assert(index >= 0 && index <= items->size);
        if(index == 0){
            void *returnVal = items->head->data;
            items->head->data = value;
            return returnVal;
            }
        if(index == items->size-1){
            void *returnVal = items->tail->data;
            items->tail->data = value;
            return returnVal;
            }
        if(index == items->size){
            insertDLL(items, index, value);
            return 0;
            }
        if(index < items->size/2){
            NODE *tempNode = items->head;
            int i = 0;
            for(i=0; i < index; i++){
                tempNode = tempNode->next;
                }
            void *returnVal = tempNode->data;
            tempNode->data = value;
            return returnVal;
            }
        else{
            NODE *tempNode = items->tail;
            int i = items->size-1;
            for(i=items->size-1; i > index; i--){
                tempNode = tempNode->prev;
                }
            void *returnVal = tempNode->data;
            tempNode->data = value;
            return returnVal;
            }
        }

    //returns the size of the DLL
    int sizeDLL(DLL *items){
        return items->size;
        }

    //prints the list out for you
    void displayDLL(DLL *items,FILE *FP){
        fprintf(FP,"{{");
        NODE *printNode = items->head;
        while(printNode != 0){
            items->display(printNode->data,FP);
            printNode = printNode->next;
            if(printNode != 0){
                fprintf(FP,",");
                }
            }
        fprintf(FP,"}}");
        }

    //displays the DLL but debugged: "head->{{3,1,2}},tail->{{2}}"
    void displayDLLdebug(DLL *items,FILE *FP){
        fprintf(FP,"head->");
        displayDLL(items, FP);
        fprintf(FP,",");
        NODE *tailNode = items->tail;
        fprintf(FP,"tail->");
        if(tailNode != 0){
            fprintf(FP,"{{");
            items->display(items->tail->data,FP);
            fprintf(FP,"}}");
            }
        else{
            fprintf(FP,"{{}}");
            }
        }
    //free every node and value in the DLL using the freeing function passed in
    void freeDLL(DLL *items){
        NODE *freeNode = items->head;
        NODE *nextNode = items->head;
        while(freeNode != 0){
            if(items->free != 0){
                items->free(freeNode->data);
                }
            nextNode = nextNode->next;
            free(freeNode);
            freeNode = nextNode;
            }
        free(items);
        }
