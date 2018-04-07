#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "scanner.h"
#include "string.h"
#include "gst.h"
#include "avl.h"

/*
trees -g corpus commands

-g = GST
-r = AVL
-v = author's name

corpus = file of text

commands = file which contains a sequence of commands

--Store everything from the corpus into the tree then run the Commands.
*/

int version = 0;            //-v
int storeGST = 0;           //-g
int storeAVL = 0;           //-r
char *inputName = NULL;     //input filename
char *inputComm = NULL;     //input commands

static void processCommandLineArgs(int argc, char **argv);
static void readFileToGST(GST *gst);
static void readFileToAVL(AVL *avl);
static int cleanReadString(char *string);
static void runCommandsGST(GST *gst);
static void runCommandsAVL(AVL *avl);

int main(int argc, char **argv){
    processCommandLineArgs(argc, argv);
    if(version){
        printf("Written by Mr. Fantastic Reid Dewberry\n");
        return 0;
        }
    if(storeGST == 1){
        GST *gst = newGST(displaySTRING, compareSTRING, freeSTRING);
        readFileToGST(gst);
        runCommandsGST(gst);
        }
    if(storeAVL == 1){
        AVL *avl = newAVL(displaySTRING, compareSTRING, freeSTRING);
        readFileToAVL(avl);
        runCommandsAVL(avl);
        }
    }

void processCommandLineArgs(int argc, char **argv){
    assert(argc > 0);
    if(argc < 3){
        if(argv[1][1] == 'v' && argv[1][0] == '-'){
            version = 1;
            return;
            }
        }
    if(argv[1][0] == '-'){
        switch(argv[1][1]){
            case 'g':
                storeGST = 1;
                break;
            case 'r':
                storeAVL = 1;
                break;
            }
        inputName = argv[2];
        inputComm = argv[3];
        }
    else{
        storeAVL = 1;
        inputName = argv[1];
        inputComm = argv[2];
        }
    }

void readFileToGST(GST *gst){
    FILE *fp = fopen(inputName,"r");
    char *value = NULL;
    int check = 0;
    while(!feof(fp)){
        if(stringPending(fp)){
            value = readString(fp);
            check = cleanReadString(value);
            if(check != 0){
                STRING *insertValue = newSTRING(value);
                insertGST(gst, insertValue);
                }
            }
        else{
            value = readToken(fp);
            check = cleanReadString(value);
            if(check != 0){
                STRING *insertValue = newSTRING(value);
                insertGST(gst, insertValue);
                }
            }
        }
    }

void readFileToAVL(AVL *avl){
    FILE *fp = fopen(inputName,"r");
    char *value = NULL;
    int check = 0;
    while(!feof(fp)){
        if(stringPending(fp)){
            value = readString(fp);
            check = cleanReadString(value);
            if(check != 0){
                STRING *insertValue = newSTRING(value);
                insertAVL(avl, insertValue);
                }
            }
        else{
            value = readToken(fp);
            check = cleanReadString(value);
            if(check != 0){
                STRING *insertValue = newSTRING(value);
                insertAVL(avl, insertValue);
                }
            }
        }
    }

int cleanReadString(char *source){
    int j = 0;
    int i = 0;
    if(source == NULL){
        return 0;
        }
    while(source[i] < 65 || (source[i] > 90 && source[i] < 97) || source[i] > 122){
        i += 1;
        if(source[i] == '\0'){
            source = NULL;
            return 0;
            }
        }
    int whiteRan = 0;
    int leng = strlen(source);
    char spaceTemp = '\0';
    for(i=i; i < leng; i++){
        //if Capital Letters, make Lowercase
        if(source[i] > 64 && source[i] < 91){
            if(whiteRan == 1){
                source[j] = spaceTemp;
                j += 1;
                }
            source[j] = source[i] += 32;
            j += 1;
            whiteRan = 0;
            }
        //if its white space
        else if(source[i] == 9 || source[i] == 13 || source[i] == 32 || source[i] == 10){
            if(whiteRan == 0){
                spaceTemp = source[i];
                whiteRan = 1;
                }
            }
        //if valid input
        else if(source[i] <= 122 && source[i] >= 97){
            if(whiteRan == 1){
                source[j] = spaceTemp;
                j += 1;
                }
            source[j] = source[i];
            j += 1;
            whiteRan = 0;
            }
        //if not valid input
        else{
            }
        }
    if(j == 0){
        return 0;
        }
    source[j] = '\0';
    return 1;
    }

/*
i W - insert word or phrase W into the tree
d W - delete word or phrase W from the tree
f W - report the frequency of word or phrase W
s   - show the tree
r   - report statistics
*/

void runCommandsGST(GST *gst){
    FILE *fp = fopen(inputComm,"r");
    char value = '\0';
    char *strVal = NULL;
    int check = 0;
    while(!feof(fp)){
        stringPending(fp);
        value = readChar(fp);
        if(value == 'i'){
            if(stringPending(fp)){
                strVal = readString(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *insertValue = newSTRING(strVal);
                    insertGST(gst, insertValue);
                    }
                }
            else{
                strVal = readToken(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *insertValue = newSTRING(strVal);
                    insertGST(gst, insertValue);
                    }
                }
            }
        else if(value == 'd'){
            if(stringPending(fp)){
                strVal = readString(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *strVald = newSTRING(strVal);
                    STRING *node = deleteGST(gst, strVald);
                    if(findGSTcount(gst,strVald) == 0 && node == 0){
                        fprintf(stdout,"Value %s not found.\n",getSTRING(strVald));
                        }
                    else{free(node);}
                    free(strVald);
                    }
                }
            else{
                strVal = readToken(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *strVald = newSTRING(strVal);
                    STRING *node = deleteGST(gst, strVald);
                    if(findGSTcount(gst,strVald) == 0 && node == 0){
                        fprintf(stdout,"Value %s not found.\n",getSTRING(strVald));
                        }
                    else{free(node);}
                    free(strVald);
                    }
                }
            }
        else if(value == 'f'){
            if(stringPending(fp)){
                char *strVal = readString(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *strValFind = newSTRING(strVal);
                    int freq = findGSTcount(gst, strValFind);
                    free(strValFind);
                    fprintf(stdout,"Frequency of %s: %d\n",strVal,freq);
                    }
                }
            else{
                char *strVal = readToken(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *strValFind = newSTRING(strVal);
                    int freq = findGSTcount(gst, strValFind);
                    free(strValFind);
                    fprintf(stdout,"Frequency of %s: %d\n",strVal,freq);
                    }
                }
            }
        else if(value == 's'){
            displayGST(gst, stdout);
            }
        else if(value == 'r'){
            statisticsGST(gst, stdout);
            }
        else{
            return;
            }
        }
    }

void runCommandsAVL(AVL *avl){
    FILE *fp = fopen(inputComm,"r");
    char value = '\0';
    char *strVal = NULL;
    int check = 0;
    while(!feof(fp)){
        stringPending(fp);
        value = readChar(fp);
        if(value == 'i'){
            if(stringPending(fp)){
                strVal = readString(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *insertValue = newSTRING(strVal);
                    insertAVL(avl, insertValue);
                    }
                }
            else{
                strVal = readToken(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *insertValue = newSTRING(strVal);
                    insertAVL(avl, insertValue);
                    }
                }
            }
        else if(value == 'd'){
            if(stringPending(fp)){
                strVal = readString(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *strVald = newSTRING(strVal);
                    STRING *node = deleteAVL(avl, strVald);
                    if(findAVLcount(avl,strVald) == 0 && node == 0){
                        fprintf(stdout,"Value %s not found.\n",getSTRING(strVald));
                        }
                    else{free(node);}
                    free(strVald);
                    }
                }
            else{
                strVal = readToken(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *strVald = newSTRING(strVal);
                    STRING *node = deleteAVL(avl, strVald);
                    if(findAVLcount(avl,strVald) == 0 && node == 0){
                        fprintf(stdout,"Value %s not found.\n",getSTRING(strVald));
                        }
                    else{free(node);}
                    free(strVald);
                    }
                }
            }
        else if(value == 'f'){
            if(stringPending(fp)){
                char *strVal = readString(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *strValFind = newSTRING(strVal);
                    int freq = findAVLcount(avl, strValFind);
                    free(strValFind);
                    fprintf(stdout,"Frequency of %s: %d\n",strVal,freq);
                    }
                }
            else{
                char *strVal = readToken(fp);
                check = cleanReadString(strVal);
                if(check != 0){
                    STRING *strValFind = newSTRING(strVal);
                    int freq = findAVLcount(avl, strValFind);
                    free(strValFind);
                    fprintf(stdout,"Frequency of %s: %d\n",strVal,freq);
                    }
                }
            }
        else if(value == 's'){
            displayAVL(avl, stdout);
            }
        else if(value == 'r'){
            statisticsAVL(avl, stdout);
            }
        }
    }
