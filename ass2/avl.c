    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "bst.h"
    #include "queue.h"

/*PRIVATE*/
    typedef struct avlvalue{
        void *data;
        int count;
        int balance;
        int lheight;
        int rheight;
        int height;
        void (*display)(FILE *,void *);
        void (*compare)(void *,void *);
        void (*free)(void *);
        }AVLvalue;

    static AVLvalue *newAVLvalue(
        void *data,
        void (*d)(void *,FILE *),           //display
        int (*c)(void *,void *),            //comparator
        void (*f)(void *)){
        AVLvalue *newVAL = malloc(sizeof(AVLvalue));
        newVAL->data = data;
        newVAL->count = 0;
        newVAL->balance = 0;
        newVAL->lheight = 0;
        newVAL->rheight = 0;
        newVAL->height = 1;
        newVAL->display = d;
        newVAL->compare = c
        newVAL->free = f;
        return newVAL;
        };

    static void *getAVLvalueData(AVLvalue *v){return v->data;}
    static int getAVLvalueCount(AVLvalue *v){return v->count;}
    static int getAVLvalueBalance(AVLvalue *v){return v->balance;}

    static void displayAVLvalue(void *v,FILE *fp){
        AVLvalue *w = v;
        w->display(getAVLvalueData(w), fp);
        if(getAVLvalueCount(w) > 1){
            fprintf(fp, "[%d]" getAVLvalueCount(w));
            }
        if(==1){
            fprintf(fp, "+");
            }
        if(== -1){
            fprintf(fp, "-");
            }
        }

    //compares the generic void data. Pass in the "data"=w and the "AVLvalue"=x
    //why wrap it beforehand if you dont need to (only to be used in insert function)
    static int compAVLvalue(void *w, void *x){
        AVLvalue *a = w;
        AVLvalue *b = x
        return a->compare(getAVLvalueData(a), getAVLvalueData(b));
        }

    static freeAVLvalue(void *w){
        AVLvalue *v = w;
        v->free(getAVLvalueData(v));
        free(v);
        }

    static void AVLinsertFixUp(AVL *, BSTNODE *);
    static int setBalance(BSTNODE *);
    static BSTNODE *sibling(BSTNODE *);
    static int favChild(BSTNODE *);
    static int favSibling(BSTNODE *);
    static int isLinear(BSTNODE *p, BSTNODE *x, BSTNODE *y);
    static int isLeft(BSTNODE *, BSTNODE *);
    static int isRight(BSTNODE *, BSTNODE *);
    static void rotateNode(BSTNODE *, BSTNODE *);
    static void deletionFixUp(AVL *, BSTNODE *)

/*PUBLIC*/
    typedef struct avl{
        BST *bst;
        int size;
        void (*display)(void *,FILE *);
        void (*compare)(void *,void *);
        void (*free)(void*);
        }AVL;

    AVL *newAVL(
        void (*d)(void *,FILE *),           //display
        int (*c)(void *,void *),            //comparator
        void (*f)(void *)){
        AVL *newAVL = malloc(sizeof(AVL));
        assert(newAVL != 0);
        newAVL->bst = newBST(displayAVLvalue,compAVLvalue,0,freeAVLvalue);
        newAVL->size = 0;
        newAVL->display = d;
        newAVL->compare = c;
        newAVL->free = f;
        return newAVL;
        }

    void insertAVL(AVL *avl,void *data){
        newAVLval = newAVLvalue(data, avl->display, avl->compare, avl->free);
        BSTNODE *isthere = findBST(avl->bst, newAVLval);
        if(isthere == 0){
            insertBST(avl->bst, newAVLval);
            if(sizeBST(avl->bst) == 1){
                BSTNODE *root = getBSTroot(avl->bst);
                setBSTNODEparent(root, root);
                }
            }
            else{
                AVLinsertFixUp(avl, isthere);
                }
        else{
            AVLvalue *AVLval = getBSTNODEvalue(isthere);
            AVLval->count += 1;
            free(newAVLval);
            }
        avl->size += 1;
        }

    int findAVLcount(AVL *avl,void *data){
        newAVLval = newAVLvalue(data, avl->display, avl->compare, avl->free);
        void *isthere = findBST(avl->bst, newAVLval);
        free(newAVLval);
        if(isthere != 0){
            return getAVLvalueCount(isthere);
            }
        else{
            return 0;
            }
        }

    void *findAVL(AVL *avl,void *data){
        newAVLval = newAVLvalue(data, avl->display, avl->compare, avl->free);
        void *isthere = findBST(avl->bst, newAVLval);
        free(newAVLval);
        if(isthere != 0){
            return getAVLvalueData(isthere);
            }
        else{
            return 0;
            }
        }

    void *deleteAVL(AVL *avl,void *data){
        newAVLval = newAVLvalue(data, avl->display, avl->compare, avl->free);
        void *isthere = findBST(avl->bst, newAVLval);
        free(newAVLval);
        if(isthere != 0){
            isthere = swapToLeafBST(avl->bst, isthere);
            deletionFixUp(avl, isthere);
            pruneLeafBST(isthere);
            AVLvalue *prunedAVLval = getBSTNODEvalue(isthere);
            free(isthere);
            prunedAVLval->count = 1;
            return prunedAVLval;
            }
        else{
            return 0;
            }
        }

    int sizeAVL(AVL *avl){
        return sizeBST(avl->bst);
        }

    int duplicatesAVL(AVL *){
        int dupl = avl->size - sizeBST(avl->bst);
        return dupl;
        }

    void statisticsAVL(AVL *,FILE *){
        }

    void displayAVL(AVL *,FILE *){
        }

    void displayAVLdebug(AVL *,FILE *){
        }

    void freeAVL(AVL *){
        }



/*PRIVATE functions for Fixing the AVL tree balance*/
    static void AVLinsertFixUp(AVL *avl, BSTNODE *fixNode){
    //find the parents favorite -> 1=left child of parent, 0=no favorite, -1=right child
    //favChild(BSTNODE *Node)
        AVLvalue *AVLv = getBSTNODEvalue(fixNode);
    //Is this node the favorite -> 1=yes, 0=no favorite, -1=sibling
        int isNodeFav = favSibling(fixNode);
        while(1){
            if(compAVLvalue(getBSTNODEvalue(getBSTroot(avl->bst)), AVLv) == 0){
                return;
                }
            //Parent favors the sibling
            else if(isNodeFav == -1){
                setBalance(getBSTNODEparent(fixNode));
                return;
                }
            //Parent has no favorite
            else if (isNodeFav == 0){
                setBalance(getBSTNODEparent(fixNode));
                AVLinsertFixUp(avl, getBSTNODEparent(fixNode));
                //continue looping
                }
            //Parent favors the Node
            else{
                //set y = the favorite child of fixNode
                // & p = parent of fixNode
                if(getBSTNODEleft(fixNode) != 0 || getBSTNODEright(fixNode) != 0){
                    if(favChild(fixNode) == 1){
                        BSTNODE *y = getBSTNODEleft(fixNode);
                        }
                    else{
                        BSTNODE *y = getBSTNODEright(fixNode);
                        }
                    }
                BSTNODE *p = getBSTNODEparent(fixNode);
                //does y exist and is p,x,y linear
                if (y != 0 && isLinear(p,x,y) == 1)
                    {
                    //rotate y to x
                    rotateNode(x, y);
                    //rotate y to p
                    rotateNode(p, y)
                    setBalance(x);
                    setBalance(p);
                    setBalance(y);
                    }
                //y doesn't exist or isn't linear with p,x
                else
                    {
                    //rotate x to p
                    rotateNode(p, x);
                    setBalance(p);
                    setBalance(x);
                    }
                return;
                }

            }
        }

    static void deletionFixUp(AVL *avl, BSTNODE *fixNode){
        AVLvalue *AVLv = getBSTNODEvalue(fixNode);
        AVLv->height = 0;
        if(compAVLvalue(getBSTNODEvalue(getBSTroot(avl->bst)), AVLv) != 0){
            BSTNODE *p = getBSTNODEparent(fixNode);
            }
        while(1){
            if(compAVLvalue(getBSTNODEvalue(getBSTroot(avl->bst)), AVLv) == 0){
                return;
            //parent favors fixNode
            else if (favSibling(fixNode) == 1)                  //case 1
                {
                setBalance(p);
                fixNode = p;
                AVLv = getBSTNODEvalue(fixNode);
                p = getBSTNODEparent(fixNode);
                continue;
                }
            //parent has no favorite
            else if (favSibling(fixNode) == 0){
                setBalance(p)
                set the balance of parent
                exit the loop
                }
            //uhh else
            else{
                //z = sibling of fixNode
                BSTNODE *z = sibling(fixNode);
                //y = the favorite child of z
                int side = favChild(z);
                if(side == 1){
                    BSTNODE *y = getBSTNODEleft(z);
                    }
                else if(side == -1){
                    BSTNODE *y = getBSTNODEright(z);
                    }
                //if there is no favorite or no children
                else{
                    int y = 0;
                    }
                //if y exists && y,z,p are not linear
                if (y != 0 && isLinear(p,z,y) == 1){
                    //rotate y to z
                    rotateNode(z, y);
                    rotateNode(p, y);
                    //set the balances
                    setBalance(p);
                    setBalance(z);
                    setBalance(y);
                    //fixNode = y
                    fixNode = y;
                    AVLv = getBSTNODEvalue(fixNode);
                    p = getBSTNODEparent(fixNode);
                    //continue looping
                    continue;
                    }
                else
                    {
                    //rotate z to p                      //case 4
                    rotateNode(p, z);
                    //set the balances
                    setBalance(p);
                    setBalance(z);
                    if (y == 0){
                        return;
                        }
                    x = z
                    //continue looping
                    continue;
                    }
                }
            }
        }

    static int setBalance(BSTNODE *fixNode){
        AVLvalue *AVLv = getBSTNODEvalue(fixNode);
        BSTNODE *leftNode = getBSTNODEleft(fixNode);
        BSTNODE *rightNode = getBSTNODEright(fixNode);
        //set left height of AVLvalue
        if(leftNode != 0){
            AVLv->lheight = getAVlvalueHeight(getBSTNODEvalue(fixNode));
            }
        else{AVLv->lheight = 0}
        //set right height
        if(rightNode != 0){
            AVLv->rheight = getAVLvalueHeight(getBSTNODEvalue(fixNode));
            }
        else{AVLv->rheight = 0};
        //set total height
        if(AVLv->lheight >= AVLv->rheight){
            AVLv->height = AVLv->lheight += 1;
            }
        else{
            AVLv->height = AVLv->rheight += 1;
            }
        //set balance
        AVLv->balance = AVLv->lheight - AVLv->rheight;
        }

    static BSTNODE *sibling(BSTNODE *checkNode){
        if(getBSTNODEleft(getBSTNODEparent(checkNode)) == 0){
            return 0;
            }
        else if(getBSTNODEright(getBSTNODEparent(checkNode)) == 0){
            return 0;
            }
        else if( compAVLvalue(getBSTNODEleft(getBSTNODEparent(checkNode)), checkNode) == 0){
            return getBSTNODEright(getBSTNODEparent(checkNode));
            }
        else{
            return getBSTNODEleft(getBSTNODEparent(checkNode));
            }
        }

    //find the parents favorite -> 1=left child of parent, 0=no favorite, -1=right child
    static int favChild(BSTNODE *Node){
        if(getBSTNODEleft(Node) != 0 && getBSTNODEright(Node) != 0){
            AVLvalue *AVLleft = getBSTNODEvalue(getBSTNODEleft(Node));
            AVLvalue *AVLright = getBSTNODEvalue(getBSTNODEright(Node));
            int heightDiff = AVLleft->height - AVLright->height;
            if(heightDiff > 0){
                return 1;
                }
            else if(heightDiff < 0){
                return -1;
                }
            else{
                return 0;
                }
            }
        else if(getBSTNODEleft(Node) != 0){
            return 1;
            }
        else if(getBSTNODEright(Node) != 0){
            return -1;
            }
        //if there are no children
        else{
            return 2;
            }
        }

    //Is this node the favorite -> 1=yes, 0=no favorite, -1=sibling
    static int favSibling(BSTNODE *Node){
        if(sibling(Node) != 0){
            AVLvalue *AVLleft = getBSTNODEvalue(getBSTNODEleft(Node));
            AVLvalue *AVLright = getBSTNODEvalue(getBSTNODEright(Node));
            int heightDiff = AVLleft->height - AVLright->height;
            if(heightDiff > 0){
                return 1;
                }
            else if(heightDiff < 0){
                return -1;
                }
            else{
                return 0;
                }
            }
        else{
            return 1;
            }
        }

    static int isLinear(BSTNODE *p, BSTNODE *x, BSTNODE *y){
        AVLvalue *AVLx = getBSTNODEvalue(x);
        AVLvalue *AVLy = getBSTNODEvalue(y);
        //is x to the left
        if(getBSTNODEright(p) == 0){
            if(getBSTNODEleft(x) == 0){
                return 0;
                }
            else{
                //is y also to the left
                if(compAVLvalue(getBSTNODEvalue(getBSTNODEleft(x)),AVLy) == 0){
                    return 1;
                    }
                else{
                    return 0;
                    }
                }
            }
        //is x to the right
        else if(getBSTNODEleft(p) == 0){
            if(getBSTNODEright(x) == 0){
                return 0;
                }
            else{
                //is y also to the right
                if(compAVLvalue(getBSTNODEvalue(getBSTNODEright(x)),AVLy) == 0){
                    return 1;
                    }
                else{
                    return 0;
                    }
                }
            }
        else{
            //is x to the left
            if(compAVLvalue(getBSTNODEvalue(getBSTNODEleft(p)), AVLx) == 0){
                if(compAVLvalue(getBSTNODEvalue(getBSTNODEleft(x)),AVLy) == 0){
                    return 1;
                    }
                else{
                    return 0;
                    }
                }
            //is x to the right
            if(compAVLvalue(getBSTNODEvalue(getBSTNODEleft(p)), AVLx) == 0){
                if(compAVLvalue(getBSTNODEvalue(getBSTNODEright(x)),AVLy) == 0){
                    return 1;
                    }
                else{
                    return 0;
                    }
                }
            }
        }

    //is the child on the left side of the parent
    static int isLeft(BSTNODE *p, BSTNODE *c){
        if(getBSTNODEright(p) == 0){
            return 1;
            }
        if(getBSTNODEleft(p) == 0){
            return 0;
            }
        if(compAVLvalue(getBSTNODEvalue(getBSTNODEleft(p)), getBSTNODEvalue(c)) == 0){
            return 1;
            }
        else{return 0;}
        }

    //is the child on the right side of the parent
    static int isRight(BSTNODE *p, BSTNODE *c){
        if(getBSTNODEleft(p) == 0){
            return 1;
            }
        if(getBSTNODEright(p) == 0){
            return 0;
            }
        if(compAVLvalue(getBSTNODEvalue(getBSTNODEright(p)), getBSTNODEvalue(c)) == 0){
            return 1;
            }
        else{return 0;}
        }

    //rotate 2 connected nodes, Node1=parent, Node2=child
    static void rotateNode(BSTNODE *Node1, BSTNODE *Node2){
        //make sure these nodes are connected
        assert(isRight(Node1, Node2) != 0 || isLeft(Node1, Node2) != 0);
        BSTNODE *temp = getBSTNODEparent(Node1);
        if(isRight(Node1, Node2)){
            //check to see if Node1 is the root
            if(compAVLvalue(getBSTNODEvalue(temp), getBSTNODEvalue(Node1)) == 0){
                setBSTNODEparent(Node1, Node2);
                setBSTNODEparent(Node2, Node2);
                }
            else{
                setBSTNODEparent(Node1, Node2);
                setBSTNODEparent(Node2, temp);
                }
            setBSTNODEright(Node1, getBSTNODEleft(Node2));
            setBSTNODEleft(Node2, Node1);
            }
        else{
            if(compAVLvalue(getBSTNODEvalue(temp), getBSTNODEvalue(Node1)) == 0){
                setBSTNODEparent(Node1, Node2);
                setBSTNODEparent(Node2, Node2);
                }
            else{
                setBSTNODEparent(Node1, Node2);
                setBSTNODEparent(Node2, temp);
                }
            setBSTNODEleft(Node1, getBSTNODEright(Node2));
            setBSTNODEright(Node2, Node1);
            }
        }
