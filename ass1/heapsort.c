#include <stdio.h>
#include <stdlib.h>
#include <integer.h>
#include <real.h>
#include <string.h>
#include "stack.h"
#include "queue.h"
#include "bst.h"
#include "heap.h"

int version = 0;    //option -v
int intSort = 0;    //option -i sorts file of integers (DEFAULT)
int realSort = 0;   //option -r sorts file of reals
int strSort = 0;    //option -s sorts file of strings
int incOrd = 0;     //option -I sort in Inreasing Order (DEFAULT)
int decOrd = 0;     //option -D sort in Decreasing Order

void Fatal(){
    }

static int processOptions(int,char **){
    int argIndex;
    int argUsed;
    int separateArg;
    char *arg;
    argIndex = 1;
    while (argIndex < argc && *argv[argIndex] == '-')
        {
        /* check if stdin, represented by "-" is an argument */
        /* if so, the end of options has been reached */
        if (argv[argIndex][1] == '\0') return argIndex;
        separateArg = 0;
        argUsed = 0;
        if (argv[argIndex][2] == '\0')
            {
            arg = argv[argIndex+1];
            separateArg = 1;
            }
        else
            arg = argv[argIndex]+2;

        switch (argv[argIndex][1])
            {
            /*
             * when option has an argument, do this
             *
             *     examples are -m4096 or -m 4096
             *
             *     case 'm':
             *         MemorySize = atol(arg);
             *         argUsed = 1;
             *         break;
             *
             *
             * when option does not have an argument, do this
             *
             *     example is -a
             *
             *     case 'a':
             *         PrintActions = 1;
             *         break;
             */
            case 'n':
                Number = atoi(arg);
                argUsed = 1;
                break;
            case 's':
                Special = 1;
                break;
            case 'N':
                Name = strdup(arg);
                argUsed = 1;
                break;
            default:
                Fatal("option %s not understood\n",argv[argIndex]);
            }
        if (separateArg && argUsed)
            ++argIndex;
        ++argIndex;
        }
    return argIndex;
    }

int main(int argc,char **argv){
    int argIndex = 0;

    if(argc == 1){Fatal("%d arguements!\n",argc-1);}

    argIndex = processOptions(argc,argv);

    if(argIndex == argc){
        }
    else{
        
        }
    return 0;
    }
