#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "stack.h"
#include "queue.h"
#include "heap.h"

int
main(void)
    {
    srandom(1);
    //simple INTEGER test of HEAP
    HEAP *p = newHEAP(displayINTEGER,compareINTEGER,freeINTEGER);
    insertHEAP(p,newINTEGER(3));
    insertHEAP(p,newINTEGER(0));
    insertHEAP(p,newINTEGER(2));
    buildHEAP(p);
    printf("in-order: ");
    displayHEAP(p,stdout);
    printf("\n");
    printf("level: ");
    displayHEAPdebug(p,stdout);
    printf("min should be %d\n",getINTEGER(peekHEAP(p)));
    INTEGER *r = extractHEAP(p);
    printf("min is %d\n",getINTEGER(r));
    freeINTEGER(r);
    printf("in-order: ");
    displayHEAP(p,stdout);
    printf("\n");
    printf("level: ");
    displayHEAPdebug(p,stdout);
    printf("min should be %d\n",getINTEGER(peekHEAP(p)));
    r = extractHEAP(p);
    printf("min is %d\n",getINTEGER(r));
    freeINTEGER(r);
    printf("in-order: ");
    displayHEAP(p,stdout);
    printf("\n");
    printf("level: ");
    displayHEAPdebug(p,stdout);
    printf("size: %d\n",sizeHEAP(p));
    freeHEAP(p);
    return 0;
    }
