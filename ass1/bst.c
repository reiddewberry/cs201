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
        BSTNODE *bstNode = malloc(sizeof(BSTNODE));
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
        node->data = value;
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
        int (*comp)(void *, void *);
        void (*swap)(BSTNODE *move, BSTNODE *dest);
        void (*free)(void *);
        }BST;

    BST *newBST(
        void (*display)(void *value,FILE *FP),               //display
        int (*comp)(void *value,void *value),           //comparator. - lt, 0 eq, +  gt
        void (*swap)(BSTNODE *move,BSTNODE *destination),    //swapper
        void (*free)(void *value)){                          //free
        BST *newBST = malloc(sizeof(BST));
        assert(newBST != 0);
        newBST->root = 0;
        };

    BSTNODE *getBSTroot(BST *tree){
        return tree->root;
        }

    void setBSTroot(BST *tree,BSTNODE *replacement){
        tree->root = replacement;
        }

    void setBSTsize(BST *tree,int size){
        tree->size = size;
        }

    BSTNODE *insertBST(BST *tree,void *value){
        BSTNODE *newNode = malloc(sizeof(BSTNODE));
        assert(newNode != 0);
        newNode->data = value;
        if(tree->root == 0){
            tree->root = newNode;
            return newNode;
            }
        BSTNODE *compNode = tree->root;
        while(1){
        if(tree->comp(newNode->data,compNode->data) < 0){
                if(compNode->left == 0){
                    compNode->left = newNode;
                    newNode->parent = compNode;
                    return newNode;
                    }
                compNode = compNode->left;
                }
            else{
                if(compNode->right == 0){
                    compNode->right = newNode;
                    newNode->parent = compNode;
                    return newNode;
                    }
                compNode = compNode->right;
                }
            }
        }

    BSTNODE *findBST(BST *tree,void *value){
        BSTNODE *compNode = tree->root;
        while(1){
            if(tree->comp(value,compNode->data) < 0){
                if(compNode->left == 0){
                    return 0;
                    }
                compNode = compNode->left;
                }
            else{
                if(tree->comp(value,compNode->data) == 0){
                    return compNode;
                    }
                if(compNode->right == 0){
                    return 0;
                    }
                compNode = compNode->right
                }
            }
        }


    BSTNODE *swapToLeafBST(BST *t,BSTNODE *node){
        
        }

    void pruneLeafBST(BST *t,BSTNODE *leaf){
        
        }

    BSTNODE *deleteBST(BST *t,void *value){
        
        }

    int sizeBST(BST *t){
        
        }

    void statisticsBST(BST *t,FILE *fp){
        
        }

    void displayBST(BST *t,FILE *fp){
        
        }

    void displayBSTdebug(BST *t,FILE *fp){
        
        }

    void freeBST(BST *t){
        }
