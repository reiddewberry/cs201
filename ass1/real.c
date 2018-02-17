#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "real.h"

struct REAL
    {
    double value;
    };

REAL *
newREAL(double x)
    {
    REAL *p = malloc(sizeof(REAL));
    assert(p != 0);
    p->value = x;
    return p;
    }

double
getREAL(REAL *v)
    {
    return v->value;
    }

double
setREAL(REAL *v,double x)
    {
    double old = v->value;
    v->value = x;
    return old;
    }

void
displayREAL(void *v,FILE *fp)
    {
    fprintf(fp,"%lf",getREAL((REAL *) v));
    }

int
compareREAL(void *real1,void *real2)
    {
    double temp = getREAL((REAL *) real1) - getREAL((REAL *) real2);
    if(temp < 0)
        {
        return -1;
        }
    if(temp > 0)
        {
        return 1;
        }
    else{
        return 0;
        }
    }

int
compareREALdec(void *real1,void *real2)
    {
    double temp = getREAL((REAL *) real2) - getREAL((REAL *) real1);
    if(temp < 0)
        {
        return -1;
        }
    if(temp > 0)
        {
        return 1;
        }
    else{
        return 0;
        }
    }

void
freeREAL(void *v)
    {
    free((REAL *)v);
    }
