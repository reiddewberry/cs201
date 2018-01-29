#include <stdio.h>

    struct NODE
	{
	void *data;
	NODE *prev;
	NODE *next;
	};

    struct DLL
	{
	NODE *head;
	NODE *tail;
	int size;
	void *(display)(void *,FILE *);
	void *(free)(void *);
	};


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

    void insertDLL(DLL *items,int index,void *value){
	assert(index >= 0 && index <= items->size);
	NODE *newNode = malloc(sizeof(NODE));
	newNode->data = value;
	if(index == 0){
	    newNode->next = items->head;
	    items->head->prev = newNode;
	    items->head = newNode;
	    items->size += 1;
	    }
	else if(index == items->size){
	    items->tail->next = newNode;
	    newNode->prev = items->tail;
	    items->tail = newNode;
	    items->size += 1;
	    }
	else if(index < items->size/2){
	    int i = 0;
	    NODE *tempNode = items->head;
	    for(i=0; i < index; i++){
		tempNode = tempNode->next;
		}
	    newNode->next = tempNode;
	    newNode->prev = tempNode->prev
	    tempNode->prev->next = newNode;
	    tempNode->prev = newNode;
	    items->size += 1;
	    }
	else{
	    int i = items->size;
	    NODE *tempNode = items->tail;
	    for(i=items->size; i > index; i++){
		tempNode = tempNode->prev;
		} 
	    newNode->next = tempNode;
	    newNode->prev = tempNode->prev
	    tempNode->prev->next = newNode;
	    tempNode->prev = newNode;
	    items->size += 1;
	    }
	}
	
    void *removeDLL(DLL *items,int index){
	assert(items->size > 0 && index >= 0 && index < items->size);
	if(index < items->size/2){
	    NODE *removeNode = items->head;
	    
	    }
	else{
	    NODE *removeNode = items->tail;
	    
	    }
	
	
	}
	
    void unionDLL(DLL *recipient,DLL *donor){
	
	}
	
    void *getDLL(DLL *items,int index){
	
	}
	
    void *setDLL(DLL *items,int index,void *value){ 
	
	}
	
    int sizeDLL(DLL *items){
	
	}
	
    void displayDLL(DLL *items,FILE *){
	
	}
	
    void displayDLLdebug(DLL *items,FILE *){
	
	}

    void freeDLL(DLL *items){
	
	}

