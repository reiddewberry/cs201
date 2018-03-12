#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(10);
    DLL *p = newDLL(displayINTEGER,freeINTEGER);
    int i;
    for (i = 0; i < 1000000; ++i)
        {
        int j = random() % 100;
        insertDLL(p,0,newINTEGER(j));
        }
    if (sizeDLL(p) < 100)
        {
        displayDLL(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeDLL(p));
    printf("value at 69295 is %d\n",getINTEGER(getDLL(p,69295)));
    printf("setting value at 69295 to 8\n");
    freeINTEGER(setDLL(p,69295,newINTEGER(8)));
    printf("value at 69295 now is %d\n",getINTEGER(getDLL(p,69295)));
    freeDLL(p);
    return 0;
    }
