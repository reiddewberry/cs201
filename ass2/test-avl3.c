#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "queue.h"
#include "bst.h"
#include "avl.h"

void srandom(unsigned int);
long int random(void);

int
main(void)
    {
    srandom(104);
    //INTEGER test of AVL, nominal size is 15
    int i;
    AVL *p = newAVL(displayINTEGER,compareINTEGER,freeINTEGER);
    for (i = 0; i < 15; ++i)
        {
        int j = random() % 15;
        INTEGER *a = newINTEGER(j);
        if (findAVL(p,a) == 0){
            printf("\ninserting: %d\n", getINTEGER(a));
            insertAVL(p,a);
            }
        else{
            printf("\ninserting: %d\n", getINTEGER(a));
            insertAVL(p,a);
            freeINTEGER(a);
            }
        }
    if (sizeAVL(p) < 200)
        {
        printf("AVL:\n");
        displayAVL(p,stdout);
        printf("debug: ");
        displayAVLdebug(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeAVL(p));
    statisticsAVL(p,stdout);
    freeAVL(p);
    return 0;
    }
