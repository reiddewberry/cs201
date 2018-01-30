#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "dll.h"
#include "integer.h"

int
main(void)
    {
    STACK *p = newSTACK(displayINTEGER,freeINTEGER);
    FILE *fp;
    fp = fopen("stack_test_output.txt", "w");

    int i=0;
    while(i < 1000000)
    {
        push(p,newINTEGER(1));
        i++;
    }
    INTEGER *num;
    i=0;
    while(i < 1000000)
    {
        num = pop(p);
        displayINTEGER(num, fp);
        freeINTEGER(num);
        fprintf(fp,"\n");
        i++;
    }
    displaySTACK(p, fp);
    fclose(fp);
    freeSTACK(p);
    return 0;
    }
