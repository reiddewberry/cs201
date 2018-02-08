    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
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

    void *getBSTNODEvalue(BSTNODE *node){
        return node->data;
        }

    void setBSTNODEvalue(BSTNODE *node,void *value){
        node->data = value;
        }

    BSTNODE *getBSTNODEleft(BSTNODE *node){
        if(node->left == 0){
            return 0;
            }
        return node->left;
        }

    void setBSTNODEleft(BSTNODE *node,BSTNODE *replacement){
        node->left = replacement;
        }

    BSTNODE *getBSTNODEright(BSTNODE *node){
        if(node->right == 0){
            return 0;
            }
        return node->right;
        }

    void setBSTNODEright(BSTNODE *node,BSTNODE *replacement){
        node->right = replacement;
        }

    BSTNODE *getBSTNODEparent(BSTNODE *node){
        if(node->parent == 0){
            return 0;
            }
        return node->parent;
        }

    void setBSTNODEparent(BSTNODE *node,BSTNODE *replacement){
        node->parent = replacement;
        }

    void freeBSTNODE(BSTNODE *node,void (*freefunct)(void *value)){
        if(freefunct == 0){
            freefunct(node->data);
            }
        free(node);
        }

//Binary Search Tree section from here on

    void swapFunct(BSTNODE *move,BSTNODE *dest){
        void *valHolder = move->data;
        move->data = dest->data;
        dest->data = valHolder;
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
        void (*display)(void *value,FILE *FP),        //display
        int (*comp)(void *val1,void *val2),           //comparator. - lt, 0 eq, +  gt
        void (*swap)(BSTNODE *move,BSTNODE *dest),    //swapper
        void (*free)(void *value)){                   //free
        BST *newBST = malloc(sizeof(BST));
        assert(newBST != 0);
        newBST->root = 0;
        newBST->display = display;
        newBST->comp = comp;
        if(swap == 0){
            newBST->swap = swapFunct;
            }
        else{newBST->swap = swap;}
        newBST->free = free;
        return newBST;
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
            tree->size += 1;
            return newNode;
            }
        BSTNODE *compNode = tree->root;
        while(1){
            if(tree->comp(newNode->data,compNode->data) < 0){
                if(compNode->left == 0){
                    compNode->left = newNode;
                    newNode->parent = compNode;
                    tree->size += 1;
                    return newNode;
                    }
                compNode = compNode->left;
                }
            else{
                if(compNode->right == 0){
                    compNode->right = newNode;
                    newNode->parent = compNode;
                    tree->size += 1;
                    return newNode;
                    }
                compNode = compNode->right;
                }
            }
        }

    BSTNODE *findBST(BST *tree,void *value){
        BSTNODE *compNode = tree->root;
        if(tree->size == 0){
            return 0;
            }
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
                compNode = compNode->right;
                }
            }
        }

    BSTNODE *deleteBST(BST *tree,void *value){
        BSTNODE *delNode = findBST(tree,value);
        delNode = swapToLeafBST(tree,delNode);
        pruneLeafBST(tree,delNode);
        //tree->size -= 1;
        return delNode;
        }

    BSTNODE *swapToLeafBST(BST *tree,BSTNODE *node){
        BSTNODE *leafNode = node;
        if(tree->size == 0){
            return leafNode;
            }
        while(leafNode->left != 0 || leafNode->right != 0){
            if(node->right != 0){
                tree->swap(leafNode,leafNode->right);
                leafNode = leafNode->right;
                }
            if(node->left != 0){
                tree->swap(leafNode,leafNode->left);
                leafNode = leafNode->left;
                }
            }
        return leafNode;
        }

    void pruneLeafBST(BST *tree,BSTNODE *leaf){
        if(leaf == tree->root){
            tree->root = 0;
            tree->size -=1;
            return;
            }
        if(leaf->parent->right == leaf){
            leaf->parent->right = 0;
            leaf->parent = 0;
            tree->size -= 1;
            }
        else{
            leaf->parent->left = 0;
            leaf->parent = 0;
            tree->size -= 1;
            }
        }

    int sizeBST(BST *tree){
        return tree->size;
        }

    void statisticsBST(BST *tree,FILE *fp){
        fprintf(fp,"Nodes: %d\n", tree->size);
        if(tree->root == 0){
            fprintf(fp,"Minimum depth: -1");
            fprintf(fp,"Maximum depth: -1");
            return;
            }
        //min depth
        if(tree->size < 3){
            fprintf(fp,"Minimum depth: 1\n");
            }
        else{fprintf(fp,"Minimum depth: 2\n");}
        //max depth
        int max = 0;
        if(tree->size % 2 == 0){
            max = tree->size/2;
            }
        else{
            max = (tree->size+1)/2;
            }
        fprintf(fp,"Maximum depth: %d\n", max);
        }

    void displayBST(BST *tree,FILE *fp){
        if(tree->size == 0){
            fprintf(fp,"[empty]");
            }
        //BSTNODE *printNode = tree->root;
        }

    void displayBSTdebug(BST *tree,FILE *fp){
        if(tree->size == 0){return;}
        if(tree->size == -1){
            fprintf(fp,"\n*****this shouldnt happen*****\n");
            }
        printf("\n");
        //fprintf(fp,"\n  debug here: level order  \n");
        while(0){}
        //things happen
        }

    void freeBST(BST *tree){
        BSTNODE *remNode;
        while(tree->root != 0){
            remNode = swapToLeafBST(tree,tree->root);
            pruneLeafBST(tree,remNode);
            if(tree->free != 0){
                tree->free(remNode->data);
                }
            free(remNode);
            }
        }
