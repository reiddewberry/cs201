    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "gst.h"
    #include "bst.h"

/*PRIVATE*/
    typedef struct gstvalue{
        void *data;
        int count;
        void (*display)(void *,FILE *);
        int (*compare)(void *,void *);
        void (*free)(void *);
        }GSTvalue;

    static GSTvalue *newGSTvalue(
        void *data,                          //data passed in
        void (*d)(void *,FILE *),            //display
        int (*c)(void *,void *),             //comparator
        void (*f)(void *)){                  //freeing function
        GSTvalue *newVAL = malloc(sizeof(GSTvalue));
        newVAL->data = data;
        newVAL->count = 1;
        newVAL->display = d;
        newVAL->compare = c;
        newVAL->free = f;
        return newVAL;
        };

    static void *getGSTvalue(GSTvalue *v){return v->data;}
    static int getGSTcount(GSTvalue *v){return v->count;}

    static void displayGSTV(void *v, FILE *fp){
        GSTvalue *w = v;
        w->display(w->data, fp);
        if(w->count > 1){
            fprintf(fp,"[%d]", getGSTcount(w));
            }
        }

    static int compGSTV(void *w, void *x){
        GSTvalue *a = w;
        GSTvalue *b = x;
        return a->compare(a->data, b->data);
        }

    static void freeGSTV(void *v){
        GSTvalue *w = v;
        if(w->free != 0){
            w->free(getGSTvalue(w));
            }
        free(w);
        }

/*PUBLIC*/
    typedef struct gst{
        BST *bst;
        int size;
        void (*display)(void *,FILE *);
        int (*compare)(void *,void *);
        void (*free)(void *);
        }GST;

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
        return newGST;
        };


    void insertGST(GST *gst,void *value){
        GSTvalue *newGSTval = newGSTvalue(value, gst->display, gst->compare, gst->free);
        BSTNODE *isthere = findBST(gst->bst, newGSTval);
        if(isthere == 0){
            insertBST(gst->bst, newGSTval);
            BSTNODE *root = getBSTroot(gst->bst);
            if(sizeBST(gst->bst) == 1){
                setBSTNODEparent(root, root);
                }
            }
        else{
            free(newGSTval);
            GSTvalue *GSTval = getBSTNODEvalue(isthere);
            GSTval->count += 1;
            }
        gst->size += 1;
        }

    int findGSTcount(GST *gst,void *value){
        GSTvalue *newGSTval = newGSTvalue(value, gst->display, gst->compare, gst->free);
        BSTNODE *isthere = findBST(gst->bst, newGSTval);
        free(newGSTval);
        if(isthere == 0){
            return 0;
            }
        else{
            GSTvalue *GSTval = getBSTNODEvalue(isthere);
            return GSTval->count;
            }
        }

    void *findGST(GST *gst,void *value){
        GSTvalue *newGSTval = newGSTvalue(value, gst->display, gst->compare, gst->free);
        BSTNODE *isthere = findBST(gst->bst, newGSTval);
        free(newGSTval);
        if(isthere == 0){
            return 0;
            }
        else{
            GSTvalue *GSTval = getBSTNODEvalue(isthere);
            return GSTval->data;
            }
        }

    void *deleteGST(GST *gst,void *value){
        GSTvalue *newGSTval = newGSTvalue(value, gst->display, gst->compare, gst->free);
        BSTNODE *isthere = findBST(gst->bst, newGSTval);
        free(newGSTval);
        if(isthere != 0){
            GSTvalue *GSTval = getBSTNODEvalue(isthere);
            if(GSTval->count > 1){
                GSTval->count -= 1;
                gst->size -= 1;
                return 0;
                }
            else{
                deleteBST(gst->bst, GSTval);
                void *data = GSTval->data;
                free(GSTval);
                gst->size -= 1;
                return data;
                }
            }
        else{
            return 0;
            }
        }

    int sizeGST(GST *gst){
        return sizeBST(gst->bst);
        }

    int duplicatesGST(GST *gst){
        int dup = gst->size - sizeBST(gst->bst);
        return dup;
        }

    void statisticsGST(GST *gst,FILE *fp){
        fprintf(fp,"Duplicates: %d\n", duplicatesGST(gst));
        statisticsBST(gst->bst,fp);
        }

    void displayGST(GST *gst,FILE *fp){
        displayBSTdecorated(gst->bst, fp);
        }

    void displayGSTdebug(GST *gst,FILE *fp){
        displayBST(gst->bst, fp);
        }

    void freeGST(GST *gst){
        freeBST(gst->bst);
        free(gst);
        }
