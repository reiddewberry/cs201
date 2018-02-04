    #include <stdio.h>

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

    void *getBSTNODE(BSTNODE *n){
        
        }

    void setBSTNODE(BSTNODE *n,void *value){
        }

    BSTNODE *getBSTNODEleft(BSTNODE *n){
        }

    void setBSTNODEleft(BSTNODE *n,BSTNODE *replacement){
        }

    BSTNODE *getBSTNODEright(BSTNODE *n){
        }

    void setBSTNODEright(BSTNODE *n,BSTNODE *replacement){
        }

    BSTNODE *getBSTNODEparent(BSTNODE *n){
        }

    void setBSTNODEparent(BSTNODE *n,BSTNODE *replacement){
        }

    void freeBSTNODE(BSTNODE *n,void (*free)(void *)){
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
