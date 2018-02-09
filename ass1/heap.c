    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "bst.h"

    typedef struct heap{
        
        }HEAP;



    HEAP *newHEAP(
        void (*)(void *,FILE *),    //display
        int (*)(void *,void *),     //compare
        void (*)(void *)){          //free
        HEAP
        }

    void insertHEAP(HEAP *h,void *value);
    void buildHEAP(HEAP *h);
    void *peekHEAP(HEAP *h);
    void *extractHEAP(HEAP *h);
    int  sizeHEAP(HEAP *h);
    void displayHEAP(HEAP *h,FILE *fp);
    void displayHEAPdebug(HEAP *h);
    void freeHEAP(HEAP *h);
