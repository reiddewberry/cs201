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
        if(freefunct != 0){
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
        newBST->size = 0;
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
        newNode->left = 0;
        newNode->right = 0;
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
        if(delNode != 0){
            tree->size--;
            }
        return delNode;
        }

    static BSTNODE *getSuccessor(BST *tree,BSTNODE *leafNode){
        BSTNODE *initNode = leafNode;
        while(!(leafNode->left == 0 && leafNode->right == 0)){
            if(leafNode->right != 0){
                if(leafNode->right->left != 0){
                    leafNode = leafNode->right->left;
                    while(leafNode->left != 0){
                        leafNode = leafNode->left;
                        }
                    tree->swap(initNode,leafNode);
                    initNode = leafNode;
                    }
                else{
                    leafNode =leafNode->right;
                    tree->swap(initNode,leafNode);
                    initNode = leafNode;
                    }
                }
            if(leafNode->left != 0){
                leafNode = leafNode->left;
                }
            }
        tree->swap(initNode,leafNode);
        return leafNode;
        }

    static BSTNODE *getPredecessor(BST *tree,BSTNODE *leafNode){
        BSTNODE *initNode = leafNode;
        while(!(leafNode->left == 0 && leafNode->right == 0)){
            if(leafNode->left != 0){
                if(leafNode->left->right != 0){
                    leafNode = leafNode->left->right;
                    while(leafNode->right != 0){
                        leafNode = leafNode->right;
                        }
                    tree->swap(initNode,leafNode);
                    initNode = leafNode;
                    }
                else{
                    leafNode =leafNode->left;
                    tree->swap(initNode,leafNode);
                    initNode = leafNode;
                    }
                }
            if(leafNode->right != 0){
                leafNode = leafNode->right;
                }
            }
        tree->swap(initNode,leafNode);
        return leafNode;
        }

    BSTNODE *swapToLeafBST(BST *tree,BSTNODE *node){
        BSTNODE *leafNode = node;
        if(tree->size == 0 || leafNode == 0){
            return leafNode;
            }
        if(leafNode->right != 0){
            leafNode = getSuccessor(tree,leafNode);
            }
        if(leafNode->left != 0){
            leafNode = getPredecessor(tree,leafNode);
            }
        return leafNode;
        }

    void pruneLeafBST(BST *tree,BSTNODE *leaf){
        if(leaf == 0){
            return;
            }
        if(leaf == tree->root){
            tree->root = 0;
            return;
            }
        if(leaf->parent->right == leaf){
            leaf->parent->right = 0;
            leaf->parent = 0;
            }
        else{
            leaf->parent->left = 0;
            leaf->parent = 0;
            }
        }

    int sizeBST(BST *tree){
        return tree->size;
        }

    static int maxDepthBST(BSTNODE *root){
        if(root == 0){
            return 0;
            }
        else{
            int leftDepth = maxDepthBST(root->left);
            int rightDepth = maxDepthBST(root->right);
            if(leftDepth > rightDepth){
                return leftDepth+1;
                }
            else{
                return rightDepth+1;
                }
            }
        }

    static int minDepthBST(BSTNODE *root){
        if(root->left == 0 || root->right == 0){
            return 1;
            }
        if(root->left == 0){
            return minDepthBST(root->right)+1;
            }
        if(root->right == 0){
            return minDepthBST(root->left)+1;
            }
        if(minDepthBST(root->left) <= minDepthBST(root->right)){
            return minDepthBST(root->left)+1;
            }
        else{
            return minDepthBST(root->right)+1;
            }
        }

    void statisticsBST(BST *tree,FILE *fp){
        fprintf(fp,"Nodes: %d\n", tree->size);
        if(tree->root == 0){
            fprintf(fp,"Minimum depth: -1\n");
            fprintf(fp,"Maximum depth: -1\n");
            return;
            }
        //min depth
        int min = minDepthBST(tree->root);
        fprintf(fp,"Minimum dpeth: %d\n",min);
        //max depth
        int max = maxDepthBST(tree->root);
        fprintf(fp,"Maximum depth: %d\n",max);
        }

    static void preDisplayBST(BST *tree,BSTNODE *printNode,FILE *fp){
        fprintf(fp,"[");
        if(tree->size == 0){
            return;
            }
        tree->display(printNode->data,fp);
        if(printNode->left != 0){
            fprintf(fp," ");
            preDisplayBST(tree,printNode->left,fp);
            fprintf(fp,"]");
            }

        if(printNode->right != 0){
            fprintf(fp," ");
            preDisplayBST(tree,printNode->right,fp);
            fprintf(fp,"]");
            }
        }

    void displayBST(BST *tree,FILE *fp){
        preDisplayBST(tree,tree->root,fp);
        fprintf(fp,"]");
        }

    static void levelDisplayBST(BST *tree,FILE *fp){
        QUEUE *printQ = newQUEUE(0,0);
        enqueue(printQ,tree->root);
        BSTNODE *printNode;
        while(1){
            int sizeQ = sizeQUEUE(printQ);
            if(sizeQ == 0){
                break;
                }
            while(sizeQ > 0){
                printNode = peekQUEUE(printQ);
                tree->display(printNode->data,fp);
                dequeue(printQ);
                if(printNode->left != 0){
                    enqueue(printQ,printNode->left);
                    }
                if(printNode->right != 0){
                    enqueue(printQ,printNode->right);
                    }
                sizeQ -= 1;
                if(sizeQ > 0){
                    fprintf(fp," ");
                    }
                }
            fprintf(fp,"\n");
            }
        freeQUEUE(printQ);
        }

    void displayBSTdebug(BST *tree,FILE *fp){
        if(tree->size == 0){return;}
        levelDisplayBST(tree,fp);
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
        free(tree);
        }
