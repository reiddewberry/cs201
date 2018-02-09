#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"
//#include "real.h"
//#include "string.h"
#include "queue.h"

int
main(void)
    {
    srandom(1);
    //simple INTEGER test of BST
    BST *p = newBST(displayINTEGER,compareINTEGER,0,freeINTEGER);
    insertBST(p,newINTEGER(3));
    insertBST(p,newINTEGER(2));
    insertBST(p,newINTEGER(1));
    insertBST(p,newINTEGER(7));
    insertBST(p,newINTEGER(5));
    insertBST(p,newINTEGER(6));
    insertBST(p,newINTEGER(9));
    insertBST(p,newINTEGER(4));
    printf("in-order: ");
    displayBST(p,stdout);
    printf("\n");
    printf("level: ");
    displayBSTdebug(p,stdout);
    INTEGER *q = newINTEGER(2);
    printf("is ");
    displayINTEGER(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    INTEGER *r = newINTEGER(3);
    freeBSTNODE(deleteBST(p,r),freeINTEGER);
    printf("in-order: ");
    displayBST(p,stdout);
    printf("\n");
    printf("level: ");
    displayBSTdebug(p,stdout);
    printf("is ");
    displayINTEGER(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    setINTEGER(r,2);
    freeBSTNODE(deleteBST(p,r),freeINTEGER);
    insertBST(p,newINTEGER(15));
    insertBST(p,newINTEGER(0));
    insertBST(p,newINTEGER(3));
    printf("in-order: ");
    displayBST(p,stdout);
    printf("\n");
    printf("level: ");
    displayBSTdebug(p,stdout);
    printf("is ");
    displayINTEGER(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    printf("size: %d\n",sizeBST(p));
    freeINTEGER(q);
    freeINTEGER(r);
    freeBST(p);
    return 0;
    }
