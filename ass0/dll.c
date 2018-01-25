#include <stdio.h>

    struct NODE
	{
	void *data;
	NODE *prev;
	NODE *next;
	};

    struct DLL;


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

    extern void insertDLL(DLL *items,int index,void *value);
    extern void *removeDLL(DLL *items,int index);
    extern void unionDLL(DLL *recipient,DLL *donor);
    extern void *getDLL(DLL *items,int index);
    extern void *setDLL(DLL *items,int index,void *value);
    extern int sizeDLL(DLL *items);
    extern void displayDLL(DLL *items,FILE *);
    extern void displayDLLdebug(DLL *items,FILE *);
    extern void freeDLL(DLL *items);

