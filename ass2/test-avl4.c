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
    srandom(1038);
    //INTEGER test of AVL, nominal size is 16
    int i;
    AVL *p = newAVL(displayINTEGER,compareINTEGER,freeINTEGER);
    for (i = 0; i < 16; ++i)
        {
        int j = random() % 16;
        INTEGER *a = newINTEGER(j);
        if (findAVL(p,a) == 0)
            insertAVL(p,a);
        else
            {
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
    for (i = 0; i < 16; ++i)
        {
        int j = random() % 16;
        INTEGER *a = newINTEGER(j);
        int count = findAVLcount(p,a);
        if (count == 1){
            freeINTEGER(deleteAVL(p,a));
        displayAVL(p,stdout);
            }
        else if (count > 1){
            deleteAVL(p,a);
        displayAVL(p,stdout);
            }
        printf("\n");
        freeINTEGER(a);
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
