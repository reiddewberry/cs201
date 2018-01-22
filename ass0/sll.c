#include <stdio.h>
#include "sll.h"


    struct NODE
        {
        void *data;
        NODE *next;
	};

    /*The Single Linked List structure*/
    struct SLL
        {
        NODE *head;
	NODE *tail;
	int size;
	void *(display)(void *,FILE *); 
	void *(free)(void *, FILE *);
        };
 
    /*Creates a new Sinle Linked List*/
    SLL *newSLL(void (*d)(void *,FILE *),void (*f)(void *))
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
	if (item->size == 0){
            items->head = new;
	    items->tail = new;
 	    items->size += 1;		
            }

	else if(index == items->size){
	    items->tail->next = new;
	    items->tail = new;
	    items->size += 1;
	    }
	
	else{
	    NODE *tempnode = malloc(sizeof(NODE));
	    int i = 1;
	    new->next = items->head;
	    tempnode->next = items->head;
	    for (i=1; i <= index; i++){
	        new->next = new->next->next;
		if(i < index){
		    tempnode->next = tempnode->next->next;
		    }
		}
   	    tempnode->next->next = new;
	    free(tempnode);
	    items->size += 1;
	    }
        }    

    //Removes a certain node from the list
    void *removeSLL(SLL *items,int index){
	assert(items->size > 0 && index >= 0 && index < items->size);
	NODE *tempNode = items->head;
	int i = 1;
	for(i=1; i < index; i++){
	    tempNode = tempNode->next;
	    }
	
	if(tempNode == items->head){
	    void *returnVal = tempNode->data;
	    free(tempNode);
	    items->head = 0;
	    items->tail = 0;
	    items->size -= 1;
	    return returnVal;
	    }

	NODE *removeNode = tempNode->next;
	void *returnVal = removeNode->data;
	if(removeNode == items->tail){
	    items->tail = tempNode;
	    }
	free(removeNode);
	items->size -= 1;
	return returnVal;
	}
    
    //Combines 2 lists  items, index, value
    void unionSLL(SLL *recipient,SLL *donor){
	int i = 1;
	for(i=1; i <= donor->size; i++){
	    insertSLL(recipient, recipient->size, donor->head->data);
	    removeSLL(donor, 0);
	    }
	}

    //Gives you the value of the Node at a given index
    void *getSLL(SLL *items,int index){
        
        }


    void *setSLL(SLL *items,int index,void *value);
    int sizeSLL(SLL *items);
    void displaySLL(SLL *items,FILE *);
    void displaySLLdebug(SLL *items,FILE *);
    void freeSLL(SLL *items);

