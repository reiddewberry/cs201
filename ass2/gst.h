    #ifndef __GST_INCLUDED__
    #define __GST_INCLUDED__

    #include <stdio.h>

    typedef struct gst GST;

    extern GST *newGST(
        void (*)(FILE *,void *),            //display
        int (*)(void *,void *),             //comparator
        void (*)(void *));                  //freeing function
    extern void insertGST(GST *,void *);
    extern int findGSTcount(GST *,void *);
    extern void *findGST(GST *,void *);
    extern void *deleteGST(GST *,void *);
    extern int sizeGST(GST *);
    extern int duplicates(GST *);
    extern void statisticsGST(FILE *,GST *);
    extern void displayGST(FILE *,GST *);
    extern void displayGSTdebug(FILE *,GST *);
    extern void freeGST(GST *);

    #endif
