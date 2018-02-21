#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "real.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(890);
    DLL *p = newDLL(displayREAL,freeREAL);
    /* do some inserts */
    int i;
    for (i = 0; i < 10000; ++i)
        {
        int j = random() % 100;
        int k = random() % (sizeDLL(p) + 1);
        j += (random() % 100) / 100.0;
        insertDLL(p,k,newREAL(j));
        }
    /* now random inserts and removes */
    for (i = 0; i < 10000; ++i)
        {
        if (random() % 2 == 0)
            {
            int x = random() % (sizeDLL(p) + 1);
            double j = random() % 1000 / 10.0;
            insertDLL(p,x,newREAL(j));
            }
        else if (sizeDLL(p) > 0)
            {
            int x = random() % sizeDLL(p);
            freeREAL(removeDLL(p,x));
            }
        }
    if (sizeDLL(p) < 100)
        {
        displayDLL(p,stdout);
        printf("\n");
        }
    if (sizeDLL(p) > 0)
        {
        i = random() % sizeDLL(p);
        double value = (random() % 100) / 10.0;
        printf("size is %d\n",sizeDLL(p));
        printf("value at %d is %lf\n",i,getREAL(getDLL(p,i)));
        printf("setting value at %d to %lf\n",i,value);
        freeREAL(setDLL(p,i,newREAL(value)));
        printf("value at %d now is %lf\n",i,getREAL(getDLL(p,i)));
        }
    freeDLL(p);
    return 0;
    }
