#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "queue.h"
#include "real.h"
#include "scanner.h"
#include "stack.h"


/* Options booleans */
unsigned int glb_author = 0;  // -v
unsigned int glb_input_print = 0;  // -i
unsigned int glb_bst = 0;  // -b
unsigned int glb_postfix = 0;  // -p
/* Input filename */
char *glb_input = NULL;

static void processCommandLineArgs(int argc, char **argv);
static QUEUE *processInput(QUEUE *inputQueue, BST *varBst);
static void displayFunc(FILE *, void *key, void *value);
static int comparatorFunc(void *key1, void *key2);
static unsigned int isOperator(char *token);
static int operatorcmp(char op1, char op2);
static unsigned int getOperatorRank(char op);
static void displayString(FILE *fp, void *value);
static void handleOperators(QUEUE *output, STACK *operatorStack, char *operator);
static void evaluate(QUEUE *output, BST *vars);


int main(int argc, char **argv) {
    processCommandLineArgs(argc, argv);
    if (glb_author) {
        printf("Andrew J. Halaney\n");
        return 0;
    }

    // Tokenize the whole input file
    assert(glb_input);
    BST *varBst = newBST(displayFunc, comparatorFunc);
    QUEUE *inputQueue = newQUEUE(displayString);
    FILE *inputFP = fopen(glb_input, "r");
    assert(inputFP);
    char *token = readToken(inputFP);
    while (!feof(inputFP)) {
        enqueue(inputQueue, token);
        token = readToken(inputFP);
    }

    // Check for -i
    if (glb_input_print) {
        for (int i = 0; i < sizeQUEUE(inputQueue); ++i) {
            char *token = dequeue(inputQueue);
            if (token[0] == ';') {
                printf("%s\n", token);
            }
            else {
                printf("%s ", token);
            }
            enqueue(inputQueue, token);
        }
    }

    QUEUE *outputQueue = processInput(inputQueue, varBst);

    // Check for -p
    if (glb_postfix) {
        for (int i = 0; i < sizeQUEUE(outputQueue); ++i) {
            char *token = dequeue(outputQueue);
            printf("%s", token);
            if (i != sizeQUEUE(outputQueue)) {
                printf(" ");
            }
            else {
                printf("\n");
            }
            enqueue(outputQueue, token);
        }
    }

    // Check for -b
    if (glb_bst) {
        displayBST(stdout, varBst);
        printf("\n");
    }

    // Evaluate expression
    evaluate(outputQueue, varBst);

    return 0;
}


void evaluate(QUEUE *output, BST *vars) {
    STACK *stack = newSTACK(displayREAL);

    while (sizeQUEUE(output)) {
#ifdef DEBUG
        printf("\n");
        printf("Queue: ");
        displayQUEUE(stdout, output);
        printf("\n");
#endif
        char *token = dequeue(output);
#ifdef DEBUG
        printf("Dequeued Token: %s\n", token);
#endif
        if (isOperator(token)) {
#ifdef DEBUG
            printf("Stack: ");
            displaySTACK(stdout, stack);
            printf("\n");
#endif
            double operand2 = getREAL(pop(stack));
            double operand1 = getREAL(pop(stack));
#ifdef DEBUG
            printf("operand2: %f\n", operand2);
            printf("operand1: %f\n", operand1);
#endif
            switch (token[0]) {
                case '+':
                    push(stack, newREAL(operand1 + operand2));
                    break;
                case '-':
                    push(stack, newREAL(operand1 - operand2));
                    break;
                case '*':
                    push(stack, newREAL(operand1 * operand2));
                    break;
                case '/':
                    push(stack, newREAL(operand1 / operand2));
                    break;
                case '%':
                    push(stack, newREAL(fmod(operand1, operand2)));
                    break;
                case '^':
                    push(stack, newREAL(pow(operand1, operand2)));
                    break;
                default:
                    printf("Operator not allowed: %s\n", token);
                    exit(1);
            }
        }
        else {
            REAL *num;
            if (isalpha(token[0])) {
                num = findBST(vars, token);
                if (!num) {
                    printf("variable %s was not declared\n", token);
                    exit(0);
                    }
            }
            else {
                num = newREAL(strtod(token, NULL));
            }
            push(stack, num);
        }
    }
    printf("%f\n", getREAL(pop(stack)));
}


QUEUE *processInput(QUEUE *inputQueue, BST *varBst) {
    /* Implement the shunting yard algorithm */
    QUEUE *outputQueue = newQUEUE(displayString);
    STACK *opStack = newSTACK(displayString);
    while (sizeQUEUE(inputQueue)) {
        char *token = dequeue(inputQueue);
        char *endtoken;
        strtod(token, &endtoken);
        // Handle variable declarations
        if (strcmp(token, "var") == 0) {
            char *key = dequeue(inputQueue);
            dequeue(inputQueue);  // Toss = char
            REAL *value = newREAL(strtod(dequeue(inputQueue), NULL));
            insertBST(varBst, key, value);
            dequeue(inputQueue);  // Toss ; char
        }
        // Insert variable into queue (not value, used for -p option)
        else if (isalpha(token[0])) {
            enqueue(outputQueue, token);
        }
        // Handle operators
        else if (isOperator(token)) {
            handleOperators(outputQueue, opStack, token);
        }
        // Handle number
        else if (*endtoken == '\0') {
            enqueue(outputQueue, token);
        }
        // Handle left parenthesis
        else if (token[0] == '(') {
            push(opStack, token);
        }
        // Handle right parenthesis
        else if (token[0] == ')') {
            for(;;) {
                char *popped = (char *)pop(opStack);
                if (popped[0] == '(') {
                    break;
                }
                else {
                    enqueue(outputQueue, popped);
                }
            }
        }
#ifdef DEBUG
        printf("Token processed: %s\n", token);

        printf("inputQueue: ");
        displayQUEUE(stdout, inputQueue);
        printf("\n");
        printf("outputQueue: ");
        displayQUEUE(stdout, outputQueue);
        printf("\n");
        printf("opStack: ");
        displaySTACK(stdout, opStack);
        printf("\n");
        printf("\n");
#endif
    }

    while (sizeSTACK(opStack)) {
        enqueue(outputQueue, pop(opStack));
#ifdef DEBUG
        printf("outputQueue: ");
        displayQUEUE(stdout, outputQueue);
        printf("\n");
        printf("opStack: ");
        displaySTACK(stdout, opStack);
        printf("\n");
        printf("\n");
#endif
    }
    return outputQueue;
}


void handleOperators(QUEUE *output, STACK *operatorStack, char *operator) {
    while (sizeSTACK(operatorStack)) {
        char *topOperator = (char *)peekSTACK(operatorStack);
        if (topOperator[0] == '(' || operatorcmp(operator[0], topOperator[0]) > 0) {
            break;
        }
        else {
            char *popped = (char *)pop(operatorStack);
            enqueue(output, popped);
            if (sizeSTACK(operatorStack)) {
                topOperator = (char *)peekSTACK(operatorStack);
            }
        }
    }
    push(operatorStack, operator);
}


unsigned int isOperator(char *token) {
    if (token[0] == '+' || token[0] == '-' || token[0] == '*'
            || token[0] == '/' || token[0] == '%' || token[0] == '^') {
        if (token[1] == '\0') {
            return 1;
        }
        else {
            return 0;  // -5 would fall here
        }
    }
    return 0;
}


int operatorcmp(char op1, char op2) {
    unsigned int val1 = getOperatorRank(op1);
    unsigned int val2 = getOperatorRank(op2);
    if (val1 < val2)
        return -1;
    else if (val1 == val2)
        return 0;
    else
        return 1;
}


unsigned int getOperatorRank(char op) {
    switch (op) {
        case '+':
            return 0;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case '%':
            return 4;
        case '^':
            return 5;
        default:
            fprintf(stderr, "Operator '%c' has no rank\n", op);
            exit(1);
    }
}


void processCommandLineArgs(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        switch (argv[i][1]) {
            case 'v':
                glb_author = 1;
                break;
            case 'i':
                glb_input_print = 1;
                break;
            case 'b':
                glb_bst = 1;
                break;
            case 'p':
                glb_postfix = 1;
                break;
            default:
                glb_input = argv[i];
                break;
        }
    }
}


void displayFunc(FILE *fp, void *key, void *value) {
    fprintf(fp, "%s=%lf", (char *)key, getREAL((REAL *)value));
}


int comparatorFunc(void *key1, void *key2) {
    char *string1 = (char *)key1;
    char *string2 = (char *)key2;
    return strcmp(string1, string2);
}


void displayString(FILE *fp, void *value) {
    char *string = (char *)value;
    fprintf(fp, "%s", string);
}

