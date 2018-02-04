    #include <stdio.h>
    #include "bst.h"
    #include "queue.h"

    typedef struct bstnode{
        void *data;
        struct bstnode *parent;
        struct bstnode *right;
        struct bstnode *left;
        }BSTNODE;

    BSTNODE *newBSTNODE(void *value){
        newBSTNODE *bstNode = malloc(sizeof(BSTNODE));
        assert(bstNode != 0);
        bstNode->data = value;
        bstNode->parent = 0;
        bstNode->right = 0;
        bstNode->left = 0;
        return bstNode;
        }

    void *getBSTNODE(BSTNODE *node){
        return node->data;
        }

    void setBSTNODE(BSTNODE *node,void *value){
        void *returnVal = node->data;
        node->data = value;
        return returnVal;
        }

    BSTNODE *getBSTNODEleft(BSTNODE *node){
        return node->left;
        }

    void setBSTNODEleft(BSTNODE *node,BSTNODE *replacement){
        node->left = replacement
        }

    BSTNODE *getBSTNODEright(BSTNODE *node){
        return node->right;
        }

    void setBSTNODEright(BSTNODE *node,BSTNODE *replacement){
        node->right = replacement;
        }

    BSTNODE *getBSTNODEparent(BSTNODE *node){
        return node->parent;
        }

    void setBSTNODEparent(BSTNODE *node,BSTNODE *replacement){
        node->parent = replacement;
        }

    void freeBSTNODE(BSTNODE *node,void (*freefunct)(void *value)){
        if(free != 0){
            freefunct(node->data);
            }
        free(node);
        }



    typedef struct bst{
        BSTNODE *root;
        int size;
        void (*display)(void *, FILE *);

        }BST;


    BST *newBST(
        void (*display)(void *value,FILE *FP),           //display
        int (*comp)(void *value,void *value),            //comparator
        void (*swap)(BSTNODE *move,BSTNODE *destination),     //swapper
        void (*free)(void *value));                 //free

    BSTNODE *getBSTroot(BST *t);
    void    setBSTroot(BST *t,BSTNODE *replacement);
    void    setBSTsize(BST *t,int s);
    BSTNODE *insertBST(BST *t,void *value);
    BSTNODE *findBST(BST *t,void *value);
    BSTNODE *deleteBST(BST *t,void *value);
    BSTNODE *swapToLeafBST(BST *t,BSTNODE *node);
    void    pruneLeafBST(BST *t,BSTNODE *leaf);
    int     sizeBST(BST *t);
    void    statisticsBST(BST *t,FILE *fp);
    void    displayBST(BST *t,FILE *fp);
    void    displayBSTdebug(BST *t,FILE *fp);
    void    freeBST(BST *t);
