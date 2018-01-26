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
	
	}
	
    void *removeDLL(DLL *items,int index);
    void unionDLL(DLL *recipient,DLL *donor);
    void *getDLL(DLL *items,int index);
    void *setDLL(DLL *items,int index,void *value);
    int sizeDLL(DLL *items);
    void displayDLL(DLL *items,FILE *);
    void displayDLLdebug(DLL *items,FILE *);
    void freeDLL(DLL *items);

