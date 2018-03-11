    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "gst.h"
    #include "bst.h"

/*PRIVATE*/
    typedef struct gstvalue{
        void *data;
        int count;
        void (*display)(FILE *,void *);
        void (*compare)(void *,void *);
        void (*free)(void *);
        }GSTVALUE;

    static GSTVALUE *newGSTVALUE(
        void *data;                          //data passed in
        void (*d)(void *,FILE *),            //display
        int (*c)(void *,void *),             //comparator
        void (*f)(void *)){                  //freeing function
        GSTVALUE *newVAL = malloc(sizeof(GSTVALUE));
        newVAL->data = data;
        newVAL->count = 1;
        newVAL->display = d;
        newVAL->compare = c;
        newVAL->free = f;
        return newVAL;
        };

    static void *getGSTVvalue(GSTVALUE *v){return v->data;}

    static int getGSTVcount(GSTVALUE *v){return v->count;}

    static void diplayGSTV(GSTVALUE *v, FILE *fp){
        GSTVALUE *w = v;
        w->display(getGSTVvalue(w), fp);
        if(getGSTVcount(w) > 1){
            fprintf(fp, getGSTVcount(w));
            }
        }

    static int compGSTV(void *w, void *x){
        GSTVALUE *a = x;
        return a->compare(w, getGSTVvalue(a));
        }

    static void freeGSTV(void *v){
        GSTVALUE *w = v;
        w->free(getGSTVvalue(w));
        free(w);
        }

/*PUBLIC*/
    typedef struct gst{
        BST *bst;
        int size;
        void (*display)(void *,FILE *);
        void (*compare)(void *,void *);
        void (*free)(void *);
        }GST

    GST *newGST(
        void (*d)(void *,FILE *),            //display
        int (*c)(void *,void *),             //comparator
        void (*f)(void *)){                  //freeing function
        GST *newGST = malloc(sizeof(GST));
        assert(newGST != 0);
        newGST->bst = newBST(displayGSTV,compGSTV,0,freeGSTV);
        newGST->size = 0;
        newGST->display = d;
        newGST->compare = c;
        newGST->free = f;
        return items;
        };


    void insertGST(GST *gst,void *value){
        GSTVALUE *GSTValFound = findBST(gst->bst, value);
        if(GSTValFound == 0){
            GSTVALUE *newGSTVal = newGSTVALUE(value,gst->d,gst->c,gst->f);
            insertBST(gst->bst, newGSTVal);
            }
        else{
            GSTValFound->count += 1;
            }
        }

// NOT DONE

    int findGSTcount(GST *gst,void *value){
        GSTVALUE *GSTVal = getBSTNODEvalue(findBST(gst->bst,));
        return GSTVal->count;
        }

    void *findGST(GST *gst,void *value){
        }

    void *deleteGST(GST *gst,void *value){
        BSTNODE *delNode = findGSTvalue(gst,value);
        GSTVALUE *GSTVal = getBSTNODEvalue(delNode);
        return GSTVal;
        }

    int sizeGST(GST *gst){
        return gst->size;
        }

    int duplicates(GST *gst){
        return 0;
        }

    void statisticsGST(FILE *fp,GST *gst){
        }

    void displayGST(FILE *fp,GST *gst){
        if(gst->size == 0){
            fprintf(fp,"EMPTY");
            return;
            }
        }

    void displayGSTdebug(FILE *fp,GST *gst){
        }

    void freeGST(GST *gst){
        }
