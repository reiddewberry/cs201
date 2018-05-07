/*
Chandler Reid Dewberry
Binary Search Tree Program
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "queue.h"

//BST Node structure
    typedef struct bstnode{
        void *data;             //void pointer to what is passed in by the user
        struct bstnode *parent; //pointer to it's parent
        struct bstnode *right;  //pointer to it's right child
        struct bstnode *left;   //pointer to it's left child
        }BSTNODE;

//Public Function to create and initialize a BST Node
    BSTNODE *newBSTNODE(void *value){
        BSTNODE *bstNode = malloc(sizeof(BSTNODE));
        assert(bstNode != 0);
        bstNode->data = value;
        bstNode->parent = 0;
        bstNode->right = 0;
        bstNode->left = 0;
        return bstNode;
        }

/*PUBLIC BSTNODE FUNCTIONS*/

//Returns the pointer of the data that is passed into the BST Node
    void *getBSTNODEvalue(BSTNODE *node){
        return node->data;
        }

//Changes the data pointer to new data that is chosen by the user
    void setBSTNODEvalue(BSTNODE *node,void *value){
        node->data = value;
        }

    BSTNODE *getBSTNODEleft(BSTNODE *node){
        return node->left;
        }

    void setBSTNODEleft(BSTNODE *node,BSTNODE *replacement){
        node->left = replacement;
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
        if(freefunct != 0){
            freefunct(node->data);
            }
        free(node);
        }

//Binary Search Tree section

//Swap function that is used if the user does not pass one in
    void swapFunct(BSTNODE *move,BSTNODE *dest){
        void *valHolder = move->data;
        move->data = dest->data;
        dest->data = valHolder;
        }

//BST structure
    typedef struct bst{
        BSTNODE *root;                              //point to BSTNODE at root of the BST
        int size;                                   //int value of the # of Nodes
        void (*display)(void *, FILE *);            //passed in display function
        int (*comp)(void *, void *);                //passed in compare function
        void (*swap)(BSTNODE *move, BSTNODE *dest); //passed in swapping function
        void (*free)(void *);                       //passed in free function
        }BST;

/*
Public Function to create and initialize the BST
Parameters of newBST();
    display - Display function that can display whatever is stored in the BSTNODE's data
    comparator - Returns: negative number if <, 0 if ==, positive if >
    swapper - Swaps data pointers between BSTNODEs
    free - Frees whatever is stored in the BSTNODE's data
*/
    BST *newBST(
        void (*display)(void *value,FILE *FP),
        int (*comp)(void *val1,void *val2),
        void (*swap)(BSTNODE *move,BSTNODE *dest),
        void (*free)(void *value)){
        //malloc and assert to verify there is room for the 
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

/*
Used to insert new data into the BST
2 Parameters:
    tree - BST that will be inserted into
    value - whatever data the user is passing in that this tree is built for
Returns:
    The newly inserted BSTNODE at the final location
*/
    BSTNODE *insertBST(BST *tree,void *value){
        BSTNODE *newNode = newBSTNODE(value);
        //Check if the BST is empty and if so: make the Root and Increment size
        if(tree->root == 0){
            tree->root = newNode;
            tree->size += 1;
            return newNode;
            }
        //If not empty begin to search the tree until the correct placement is found
        BSTNODE *compNode = tree->root;
        while(1){
            //use the passed in comparator to compare the data within BSTNODEs
            /*if the New Data is less than the Current Node data:
              go to the current node's Left
              else: go right*/
            if(tree->comp(newNode->data,compNode->data) < 0){
                //Once an empty spot is found, place it there
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

/*
Finds the Node in the BST with the given data.
2 Parameters:
    tree - BST that will be used
    value - whatever data the user is passing in that this tree is built for
Returns:
    the Node within the BST that contains the said data or 0 if not.
*/
    BSTNODE *findBST(BST *tree,void *value){
        //Sets first BSTNODE to compare to the Root of the BST.
        BSTNODE *compNode = tree->root;
        if(tree->size == 0){
            return 0;
            }
        while(1){
            /*If the value wanted is less than the value in the current BSTNODE:
              go left
              else: go right
            */
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
/*
Finds the BSTNODE from the BST, Moves it to a leaf, and prunes it.
2 Parameters:
    tree - BST that will be used
    value - whatever data the user is passing in that this tree is built for
Returns:
    The BSTNODE that contains the value
*/
    BSTNODE *deleteBST(BST *tree,void *value){
        BSTNODE *delNode = findBST(tree,value);
        delNode = swapToLeafBST(tree,delNode);
        pruneLeafBST(tree,delNode);
        //if a Node with said value is found, decrement the size of the BST
        if(delNode != 0){
            tree->size--;
            }
        return delNode;
        }

/*
PRIVATE - Moves the Given BSTNODE to a leaf by swapping it with its Successor.
(will go to the Left if there is no successor)
2 Parameters:
    tree - BST that will be used
    leafNode - The BSTNODE that we want the successor of
Returns:
    the passed in BSTNODE but now located at a leaf.
*/
    static BSTNODE *getSuccessor(BST *tree,BSTNODE *leafNode){
        //Create a temporrary pointer to the Node that we want to Swap
        BSTNODE *initNode = leafNode;
        //As long as there is a Node either to the left or right - loop
        while(!(leafNode->left == 0 && leafNode->right == 0)){
            //Checks if there is a successor
            if(leafNode->right != 0){
                //Before swapping check if there is a closer successor to the Left
                if(leafNode->right->left != 0){
                    leafNode = leafNode->right->left;
                    //Continue Left if so until it's found
                    while(leafNode->left != 0){
                        leafNode = leafNode->left;
                        }
                    //Swap then loop
                    tree->swap(initNode,leafNode);
                    initNode = leafNode;
                    }
                //if the immediate Right is the successor, Swap and loop
                else{
                    leafNode =leafNode->right;
                    tree->swap(initNode,leafNode);
                    initNode = leafNode;
                    }
                }
            /*if there is no Node to the Right but there are to the Left:
              Set comparing Node to the next Left Node and loop*/
            if(leafNode->left != 0){
                leafNode = leafNode->left;
                }
            }
        /*Finally when there are no more Nodes to the Left or Right:
          Do a final Swap to verify the original Node is at a leaf and return*/
        tree->swap(initNode,leafNode);
        return leafNode;
        }

/*
PRIVATE - Moves the Given BSTNODE to a leaf by swapping it with its Predecessor.
(will go to the Right if there is no predecessor)
2 Parameters:
    tree - BST that will be used
    leafNode - The BSTNODE that we want the predecessor of
Returns:
    the passed in BSTNODE but now located at a leaf.
*/

    static BSTNODE *getPredecessor(BST *tree,BSTNODE *leafNode){
        //Create a temporrary pointer to the Node that we want to Swap
        BSTNODE *initNode = leafNode;
        //As long as there is a Node either to the left or right: loop
        while(!(leafNode->left == 0 && leafNode->right == 0)){
            //Check if there is a predecessor
            if(leafNode->left != 0){
                //Before swapping check if there is a closer predecessor to the Right
                if(leafNode->left->right != 0){
                    leafNode = leafNode->left->right;
                    //Continue Left if so until it's found
                    while(leafNode->right != 0){
                        leafNode = leafNode->right;
                        }
                    //Swap then loop
                    tree->swap(initNode,leafNode);
                    initNode = leafNode;
                    }
                //if the immediate Right is the successor, Swap and loop
                else{
                    leafNode =leafNode->left;
                    tree->swap(initNode,leafNode);
                    initNode = leafNode;
                    }
                }
            /*if there is no Node to the Right but there are to the Left:
              Set comparing Node to the next Left Node and loop*/
            if(leafNode->right != 0){
                leafNode = leafNode->right;
                }
            }
        /*Finally when there are no more Nodes to the Left or Right:
          Do a final Swap to verify the original Node is at a leaf and return*/
        tree->swap(initNode,leafNode);
        return leafNode;
        }

/*
Swaps a given Node to a leaf.
(Successor if there is one, if not Predecessor)
2 Parameters:
    tree - BST that will be used
    node - the BSTNODE that will be swapped to a leaf
Returns:
    The passed in BSTNODE after it is swapped to a leaf
*/
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

/*
Takes a passed in leaf Node and sets all it's pointers to 0 except the data.
As well as  setting all pointers to it as 0.
2 Parameters:
    tree - BST that will be used
    node - the BSTNODE that will be swapped to a leaf
*/
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

//Returns the size of the BST given.
    int sizeBST(BST *tree){
        return tree->size;
        }

/*
PRIVATE - Finds the Maximum Depth of the BST given.
1 Parameter:
    root - The BSTNODE at the root of the BST.
Returns:
    An integer value of the max steps to a leaf from the root.
*/
    static int maxDepthBST(BSTNODE *root){
        if(root == 0){
            return 0;
            }
        //Finds the Higher Depth to the Left and Right recursively
        else{
            int leftDepth = maxDepthBST(root->left);
            int rightDepth = maxDepthBST(root->right);
            /*Whichever depth is greater return it with an addition of 1
              (the step to the NULL child)*/
            if(leftDepth > rightDepth){
                return leftDepth+1;
                }
            else{
                return rightDepth+1;
                }
            }
        }

/*
PRIVATE - Finds the Minimum Depth of the BST given
1 Parameter:
    root - The BSTNODE at the root of the BST.
Returns:
    An integer value of the min steps to a leaf from the root.
*/
    static int minDepthBST(BSTNODE *root){
        //Find the smaller depth to the Left or Right recursively
        //When either Left or Right have a NULL child return 1
        if(root->left == 0 || root->right == 0){
            return 1;
            }
        //If the Left is smaller return it's depth +1, if not return Right depth +1
        if(minDepthBST(root->left) <= minDepthBST(root->right)){
            return minDepthBST(root->left)+1;
            }
        else{
            return minDepthBST(root->right)+1;
            }
        }

/*
Prints using whatever file pointer passed in (stdout if not).
2 Parameters:
    tree - BST that will be used
    fp - the file pointer passed in
ex.
Nodes: 7
Minimum depth: 1
Maximum depth: 3
*/
    void statisticsBST(BST *tree,FILE *fp){
        fprintf(fp,"Nodes: %d\n", tree->size);
        //If the tree is empty print the depths as -1
        if(tree->root == 0){
            fprintf(fp,"Minimum depth: -1\n");
            fprintf(fp,"Maximum depth: -1\n");
            return;
            }
        //min depth
        int min = minDepthBST(tree->root)-1;
        fprintf(fp,"Minimum depth: %d\n",min);
        //max depth
        int max = maxDepthBST(tree->root)-1;
        fprintf(fp,"Maximum depth: %d\n",max);
        }

/*
PRIVATE - Used by displayBST() to print a Pre-order Traversal of the BST given
3 Parameters:
    tree - BST that will be used
    printNode - The current Node to be printed
    fp - the file pointer passed in
ex.
[8 [3 [1] [7 [4]]] [14 [15]]]
*/
    static void preDisplayBST(BST *tree,BSTNODE *printNode,FILE *fp){
        fprintf(fp,"[");
        if(tree->size == 0){
            return;
            }
        /*Using the passed in display function
          the data with the current Node is printed to the file pointer*/
        tree->display(printNode->data,fp);
        //If there are Nodes to the Left, it recursively calls this function on the Left
        if(printNode->left != 0){
            fprintf(fp," ");
            preDisplayBST(tree,printNode->left,fp);
            fprintf(fp,"]");
            }
        //After going to the Left, it recursively is called on the Right
        if(printNode->right != 0){
            fprintf(fp," ");
            preDisplayBST(tree,printNode->right,fp);
            fprintf(fp,"]");
            }
        }

/*
Utilizes preDisplayBST() to print a Pre-order Traversal of the BST.
If the BST is empty it prints []
*/
    void displayBST(BST *tree,FILE *fp){
        preDisplayBST(tree,tree->root,fp);
        fprintf(fp,"]");
        }

/*
PRIVATE - Prints a Level-order Traversal of the BST given
A Queue is utilized to gather the Nodes in Level-order.
2 Parameters
    tree - BST that will be used
    fp - the file pointer passed in
ex.
8
3 14
1 7 15
4
*/
    static void levelDisplayBST(BST *tree,FILE *fp){
        //printQ is created to hold the values of the BST as we go down the tree
        QUEUE *printQ = newQUEUE(0,0);
        enqueue(printQ,tree->root);
        //A BSTNODE pointer is created to help clean the code and print the data.
        BSTNODE *printNode;
        while(1){
            //To know when to stop looping, we check the size of printQ
            int sizeQ = sizeQUEUE(printQ);
            if(sizeQ == 0){
                break;
                }
            while(sizeQ > 0){
                //Take the front of the queue and dequeue it to be printed
                printNode = dequeue(printQ);
                tree->display(printNode->data,fp);
                //If there is a Node to the Left, enqueue it (same to the Right after)
                if(printNode->left != 0){
                    enqueue(printQ,printNode->left);
                    }
                if(printNode->right != 0){
                    enqueue(printQ,printNode->right);
                    }
                //decrement the sizeQ and print a space if it is still greater than 0
                sizeQ -= 1;
                if(sizeQ > 0){
                    fprintf(fp," ");
                    }
                }
            //print a new line when the sizeQ is empty
            fprintf(fp,"\n");
            }
        //Afterwards free the queue used
        freeQUEUE(printQ);
        }

/*
Utilizes levelDisplayBST() to print a Level-order Traversal of the BST.
If the BST is empty it doesn't print anything
*/
    void displayBSTdebug(BST *tree,FILE *fp){
        if(tree->size == 0){return;}
        levelDisplayBST(tree,fp);
        }

/*
Frees:
    The BST passed in
    All of it's BSTNODEs
    The data within if a freeing function was passed in when the BST was created.
1 Parameter
    tree - The BST to be freed
*/
    void freeBST(BST *tree){
        BSTNODE *remNode;
        while(tree->root != 0){
            remNode = swapToLeafBST(tree,tree->root);
            pruneLeafBST(tree,remNode);
            //Frees the Data if there is a freeing function
            if(tree->free != 0){
                tree->free(remNode->data);
                }
            //Frees the BSTNODE
            free(remNode);
            }
        //After freeing all the Nodes, free the BST
        free(tree);
        }
