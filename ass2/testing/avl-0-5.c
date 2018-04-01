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
    srandom(106);
    //INTEGER test of AVL, nominal size is 189
    int i;
    AVL *p = newAVL(displayINTEGER,compareINTEGER,freeINTEGER);
    for (i = 0; i < 189; ++i)
        {
        int j = random() % 189;
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
    statisticsAVL(p,stdout);
    freeAVL(p);
    return 0;
    }
