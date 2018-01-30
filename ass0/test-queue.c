#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "sll.h"
#include "integer.h"

int
main(void)
    {
    srandom(1);
    QUEUE *p = newQUEUE(displayINTEGER,freeINTEGER);
    enqueue(p,newINTEGER(3));
    printf("The value ready for dequeue: ");
    displayINTEGER(peekQUEUE(p), stdout);
    printf("\n");
    enqueue(p,newINTEGER(4));
    printf("The value ready for dequeue: ");
    displayINTEGER(peekQUEUE(p), stdout);
    printf("\n");
    enqueue(p,newINTEGER(2));
    printf("The value ready for dequeue: ");
    displayINTEGER(peekQUEUE(p), stdout);
    printf("\n");
    displayQUEUE(p,stdout);
    printf("\n");
    void *value = dequeue(p);
    displayINTEGER(value,stdout);
    printf("\n");
    freeINTEGER(value);
    printf("The value ready for dequeue: ");
    displayINTEGER(peekQUEUE(p), stdout);
    printf("\n");
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    value = dequeue(p);
    displayINTEGER(value,stdout);
    printf("\n");
    freeINTEGER(value);
    printf("The value ready for dequeue: ");
    displayINTEGER(peekQUEUE(p), stdout);
    printf("\n");
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    freeINTEGER(dequeue(p));
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    freeQUEUE(p);
    return 0;
    }
