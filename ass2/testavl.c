    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "bst.h"
    #include "queue.h"

/*PRIVATE*/
    typedef struct avlvalue{
        void *data;
        int count;
        int balance;
        void (*display)(FILE *,void *);
        void (*compare)(void *,void *);
        void (*free)(void *);
        }AVLvalue;

    static AVLvalue *newAVLvalue(
        void *data,
        void (*d)(void *,FILE *),           //display
        int (*c)(void *,void *),            //comparator
        void (*f)(void *)){
        AVLvalue *newVAL = malloc(sizeof(AVLvalue));
        newVAL->data = data;
        newVAL->count = 0;
        newVAL->balance = 0;
        newVAL->display = d;
        newVAL->compare = c
        newVAL->free = f;
        return newVAL;
        };

    static void *getAVLvalueData(AVLvalue *v){return v->data;}
    static int getAVLvalueCount(AVLvalue *v){return v->count;}
    static int getAVLvalueBalance(AVLvalue *v){return v->balance;}

    static void displayAVLvalue(AVLvalue *v,FILE *fp){
        AVLvalue *w = v;
        w->display(getAVLvalueData(w), fp);
        if(getAVLvalueCount(w) > 1){
            fprintf(fp, getAVLvalueCount(w));
            }
        }

    //compares the generic void data. Pass in the "data"=w and the "AVLvalue"=x
    //why wrap it beforehand if you dont need to (only to be used in insert function)
    static int compAVLvalue(void *w, void *x){
        AVLvalue *a = x;
        return a->compare(w, getAVLvalueData(a));
        }

    static freeAVLvalue(AVLvalue *v){
        v->free(getAVLvalueData(v));
        free(v);
        }

/*PUBLIC*/
    typedef struct avl{
        BST *bst;
        int size;
        void (*display)(void *,FILE *);
        void (*compare)(void *,void *);
        void (*free)(void*);
        }AVL;

    AVL *newAVL(
        void (*d)(void *,FILE *),           //display
        int (*c)(void *,void *),            //comparator
        void (*f)(void *)){
        AVL *newAVL = malloc(sizeof(AVL));
        assert(newAVL != 0);
        newAVL->bst = newBST(displayAVLvalue,compAVLvalue,0,freeAVLvalue);
        newAVL->size = 0;
        newAVL->display = d;
        newAVL->compare = c;
        newAVL->free = f;
        return newAVL;
        }


    void insertAVL(AVL *,void *){
        }

    int findAVLcount(AVL *,void *){
        }

    void *findAVL(AVL *,void *){
        }

    void *deleteAVL(AVL *,void *){
        }

    int sizeAVL(AVL *){
        }

    int duplicatesAVL(AVL *){
        }

    void statisticsAVL(AVL *,FILE *){
        }

    void displayAVL(AVL *,FILE *){
        }

    void displayAVLdebug(AVL *,FILE *){
        }

    void freeAVL(AVL *){
        }
