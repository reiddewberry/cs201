#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "scanner.h"
#include "stack.h"
#include "queue.h"
#include "bst.h"
#include "heap.h"

int version = 0;    //option -v
int intSort = 0;    //option -i sorts file of integers (DEFAULT)
int realSort = 0;   //option -r sorts file of reals
int strSort = 0;    //option -s sorts file of strings
int incOrd = 0;     //option -I sort in Inreasing Order (DEFAULT)
int decOrd = 0;     //option -D sort in Decreasing Order
char *inputName = NULL; //input filename

static void processCommandLineArgs(int argc,char **argv);
static void readFileToHeap(HEAP *sortHeap);

static char *readItem(FILE *fp){
    if(stringPending(fp)){
        return readString(fp);
        }
    else{
        return readToken(fp);
        }
    }

//static for pint token or string

int main(int argc,char **argv){
    processCommandLineArgs(argc,argv);
    if(version){
        printf("Written by Reid Dewberry\n");
        printf("My heapsort works in nlog(n) time because adding a value takes contant time because the farthest right leaf is always held first in the stack and can be peeked and added to in constant time. Ordering the heap takes linear time because it calls n/2 nodes to sort and the sort takes less than log(n) therefore it is the same as the time of n. extracting the min/max takes log time because the min/max is always the root of the tree and can be swapped with the furthest right leaf. After swapping the new root must be sorted which takes log time due to the usefulness of a tree structure. Therefore alltogether it works out to nlog(n).\n");
        return 0;
        }
    assert(inputName);
    HEAP *sortHeap;
    if(realSort){
        if(decOrd){
            sortHeap = newHEAP(displayREAL,compareREALdec,freeREAL);
            }
        else{
            sortHeap = newHEAP(displayREAL,compareREAL,freeREAL);
            }
        }
    else if(strSort){
        if(decOrd){
            sortHeap = newHEAP(displaySTRING,compareSTRINGdecr,freeSTRING);
            }
        else{
            sortHeap = newHEAP(displaySTRING,compareSTRING,freeSTRING);
            }
        }
    else{
        if(decOrd){
            sortHeap = newHEAP(displayINTEGER,compareINTEGERdec,freeINTEGER);
            }
        else{
            sortHeap = newHEAP(displayINTEGER,compareINTEGER,freeINTEGER);
            }
        }
    readFileToHeap(sortHeap);
    buildHEAP(sortHeap);
    if(realSort){
        void *value = extractHEAP(sortHeap);
        displayREAL(value,stdout);
        while(sizeHEAP(sortHeap) > 0){
            printf(" ");
            free(value);
            value = extractHEAP(sortHeap);
            displayREAL(value,stdout);
            }
        freeHEAP(sortHeap);
        }
    else if(strSort){
        void *value = extractHEAP(sortHeap);
        displaySTRING(value,stdout);
        while(sizeHEAP(sortHeap) > 0){
            printf(" ");
            free(value);
            value = extractHEAP(sortHeap);
            displaySTRING(value,stdout);
            }
        freeHEAP(sortHeap);
        }
    else{
        void *value = extractHEAP(sortHeap);
        displayINTEGER(value,stdout);
        while(sizeHEAP(sortHeap) > 0){
            printf(" ");
            free(value);
            value = extractHEAP(sortHeap);
            displayINTEGER(value,stdout);
            }
        freeHEAP(sortHeap);
        }
    printf("\n");
    return 0;
    }

void processCommandLineArgs(int argc,char **argv){
    assert(argc > 0);
    if(argc < 3){
        if(argv[1][1] == 'v' && argv[1][0] == '-'){
            version = 1;
            return;
            }

        }
    for(int i=1; i<argc-1; i++){
        switch(argv[i][1]){
            case 'v':
                version = 1;
                break;
            case 'i':
                intSort = 1;
                break;
            case 'r':
                realSort = 1;
                break;
            case 's':
                strSort = 1;
                break;
            case 'I':
                incOrd = 1;
                break;
            case 'D':
                decOrd = 1;
                break;
            default:
                break;
            }
        }
    inputName = argv[argc-1];
    }

void readFileToHeap(HEAP *sortHeap){
    FILE *fp = fopen(inputName,"r");
    if(realSort){
        REAL *value = newREAL(readReal(fp));
        while(!feof(fp)){
            insertHEAP(sortHeap,value);
            value = newREAL(readReal(fp));
            }
        free(value);
        }
    else if(strSort){
        STRING *value = newSTRING(readItem(fp));
        while(!feof(fp)){
            displaySTRING(value,fp);
            insertHEAP(sortHeap,value);
            value = newSTRING(readItem(fp));
            }
        free(value);

        /*
        if(stringPending(fp)){
            STRING *value = newSTRING(readString(fp));
            while(!feof(fp)){
                insertHEAP(sortHeap,value);
                value = newSTRING(readString(fp));
                }
            free(value);
            }
        else{
            STRING *value = newSTRING(readToken(fp));
            while(!feof(fp)){
                insertHEAP(sortHeap,value);
                value = newSTRING(readToken(fp));
                }
            free(value);
            }*/

        }
    else{
        INTEGER *value = newINTEGER(readInt(fp));
        while(!feof(fp)){
            insertHEAP(sortHeap,value);
            value = newINTEGER(readInt(fp));
            }
        free(value);
        }
    fclose(fp);
    }
