#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

int
main(void)
    {
    srandom(1);
    SLL *p = newSLL(displayINTEGER,freeINTEGER);

    /*FILE *fp;
    fp = fopen("test_file.txt", "w");
    int i=0;
    for(i=0; i<1000; i++){
        int j = i/2;
        insertSLL(p,j,newINTEGER(i));
        if(i < 20){
            displaySLL(p,fp);
            fprintf(fp,"\n");
            }
        }

    for(int i=0; i<1000; i++){
        removeSLL(p,0);
        }
    displaySLL(p,fp);
    fclose(fp);
*/
    insertSLL(p,0,newINTEGER(3));
    insertSLL(p,sizeSLL(p),newINTEGER(2));
    displaySLL(p,stdout);
    printf("\n");
    freeINTEGER(removeSLL(p,1));
    displaySLL(p,stdout);
    printf("\n");
    freeINTEGER(removeSLL(p,0));
    displaySLL(p,stdout);
    printf("\n");
    SLL *q = newSLL(displayINTEGER,freeINTEGER);
    insertSLL(p,0,newINTEGER(6));
    insertSLL(p,0,newINTEGER(7));
    insertSLL(q,0,newINTEGER(4));
    insertSLL(q,0,newINTEGER(5));
    displaySLL(p,stdout);
    printf("\n");
    displaySLL(q,stdout);
    printf("\n");
    unionSLL(p,q);
    displaySLL(p,stdout);
    displaySLL(q,stdout);
    printf("\n");
    displaySLLdebug(p,stdout);
    printf("\n");
    displaySLLdebug(q,stdout);
    printf("\n");
    freeSLL(p);
    freeSLL(q);
    return 0;
    freeSLL(p);
    }
