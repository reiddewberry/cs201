    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "bst.h"
    #include "queue.h"

    typedef struct avl{
        void *data;
        }AVL;

    AVL *newAVL(
        void (*)(void *,FILE *),           //display
        int (*)(void *,void *),            //comparator
        void (*)(void *));                 //freeing function


    void insertAVL(AVL *,void *);
    int findAVLcount(AVL *,void *);
    void *findAVL(AVL *,void *);
    void *deleteAVL(AVL *,void *);
    int sizeAVL(AVL *);
    int duplicatesAVL(AVL *);
    void statisticsAVL(AVL *,FILE *);
    void displayAVL(AVL *,FILE *);
    void displayAVLdebug(AVL *,FILE *);
    void freeAVL(AVL *);
