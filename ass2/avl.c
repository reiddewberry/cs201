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
        void (*display)(void *,FILE *);
        int (*compare)(void *,void *);
        void (*free)(void *);
        }AVLvalue;

    static AVLvalue *newAVLvalue(
        void *value,
        void (*d)(void *,FILE *),           //display
        int (*c)(void *w,void *v),            //comparator
        void (*f)(void *)){
        AVLvalue *newVAL = malloc(sizeof(AVLvalue));
        newVAL->data = value;
        newVAL->count = 1;
        newVAL->balance = 0;
        newVAL->lheight = 0;
        newVAL->rheight = 0;
        newVAL->height = 1;
        newVAL->display = d;
        newVAL->compare = c;
        newVAL->free = f;
        return newVAL;
        };

    static void *getAVLvalueData(AVLvalue *v){return v->data;}
    static int getAVLvalueCount(AVLvalue *v){return v->count;}
    static int getAVLvalueBalance(AVLvalue *v){return v->balance;}

    //To be used, private
    static int setBalance(BSTNODE *);
    static BSTNODE *sibling(BSTNODE *);
    static int favChild(BSTNODE *);
    static int favSibling(BSTNODE *);
    static int isLinear(BSTNODE *p, BSTNODE *x, BSTNODE *y);
    static int isLeft(BSTNODE *, BSTNODE *);
    static int isRight(BSTNODE *, BSTNODE *);

    //compares the generic void data. Pass in the "data"=w and the "AVLvalue"=x
    //why wrap it beforehand if you dont need to (only to be used in insert function)
    static int compAVLvalue(void *w, void *x){
        AVLvalue *a = w;
        AVLvalue *b = x;
        return a->compare(getAVLvalueData(a), getAVLvalueData(b));
        }

    static void displayAVLvalue(void *v,FILE *fp){
        AVLvalue *w = v;
        w->display(getAVLvalueData(w), fp);
        if(getAVLvalueCount(w) > 1){
            fprintf(fp, "[%d]", getAVLvalueCount(w));
            }
        if(w->balance == 1){
            fprintf(fp, "+");
           }
        if(w->balance == -1){
            fprintf(fp, "-");
            }
        }

    static int getAVLvalueHeight(AVLvalue *AVLv){
        return AVLv->height;
        }

    static void freeAVLvalue(void *w){
        AVLvalue *v = w;
        if(v->free != 0){
            v->free(getAVLvalueData(v));
            }
        free(v);
        }

    static void AVLswap(BSTNODE *a, BSTNODE *b){
        AVLvalue *ta = getBSTNODEvalue(a);
        AVLvalue *tb = getBSTNODEvalue(b);

        /* swap the values stored in the AVL value objects */
        void *vtemp = ta->data;
        ta->data = tb->data;
        tb->data = vtemp;

        /* swap the counts stored in the AVL value objects */
        int ctemp = ta->count;
        ta->count = tb->count;
        tb->count = ctemp;

        /* note: AVL heights and balance factors are NOT swapped */
        }

/*PUBLIC*/
    typedef struct avl{
        BST *bst;
        int size;
        void (*display)(void *,FILE *);
        int (*compare)(void *,void *);
        void (*free)(void *);
        }AVL;

    AVL *newAVL(
        void (*d)(void *,FILE *),           //display
        int (*c)(void *,void *),            //comparator
        void (*f)(void *)){
        AVL *newAVL = malloc(sizeof(AVL));
        assert(newAVL != 0);
        newAVL->bst = newBST(displayAVLvalue,compAVLvalue,AVLswap,freeAVLvalue);
        newAVL->size = 0;
        newAVL->display = d;
        newAVL->compare = c;
        newAVL->free = f;
        return newAVL;
        }

/*PRIVATE FUNCTIONS to be used*/
    static void AVLinsertFixUp(AVL *, BSTNODE *);
    static void deletionFixUp(AVL *, BSTNODE *);
    static void rotateNode(AVL *, BSTNODE *, BSTNODE *);


//ALL FUNCTIONS

    //Inserts data wrapped in an AVLvalue into the bst
    void insertAVL(AVL *avl,void *data){
        AVLvalue *newAVLval = newAVLvalue(data, avl->display, avl->compare, avl->free);
        BSTNODE *isthere = findBST(avl->bst, newAVLval);
        if(isthere == 0){
            isthere = insertBST(avl->bst, newAVLval);
            BSTNODE *root = getBSTroot(avl->bst);
            if(sizeBST(avl->bst) == 1){
                setBSTNODEparent(root, root);
                }
            else{
                AVLinsertFixUp(avl, isthere);
                }
            }
        else{
            free(newAVLval);
            AVLvalue *AVLval = getBSTNODEvalue(isthere);
            AVLval->count += 1;
            }
        avl->size += 1;
        }

    int findAVLcount(AVL *avl,void *data){
        AVLvalue *newAVLval = newAVLvalue(data, avl->display, avl->compare, avl->free);
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
        AVLvalue *newAVLval = newAVLvalue(data, avl->display, avl->compare, avl->free);
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
        AVLvalue *newAVLval = newAVLvalue(data, avl->display, avl->compare, avl->free);
        BSTNODE *isthere = findBST(avl->bst, newAVLval);
        printf("\n\nNOW Deleting : ");
        displayAVLvalue(newAVLval, stdout);
        printf("\n");
   /*here*/      free(newAVLval);
        AVLvalue *AVLfound = getBSTNODEvalue(isthere);
        if(AVLfound->count > 1){
            AVLfound->count -= 1;
            avl->size -= 1;
            return 0;
            }
        isthere = swapToLeafBST(avl->bst, isthere);
        AVLfound->height = 0;
        deletionFixUp(avl, isthere);
        pruneLeafBST(avl->bst, isthere);
        setBSTsize(avl->bst,sizeBST(avl->bst)-1);
        avl->size -= 1;
        void *AVLdata = AVLfound->data;
        //free(AVLfound);
        free(isthere);
        return AVLdata;
        }

    int sizeAVL(AVL *avl){
        return sizeBST(avl->bst);
        }

    int duplicatesAVL(AVL *avl){
        int dupl = avl->size - sizeBST(avl->bst);
        return dupl;
        }

    void statisticsAVL(AVL *avl,FILE *fp){
        fprintf(fp,"Duplicates: %d\n", duplicatesAVL(avl));
        statisticsBST(avl->bst,fp);
        }

    void displayAVL(AVL *avl,FILE *fp){
        displayBSTdecorated(avl->bst,fp);
        }

    void displayAVLdebug(AVL *avl,FILE *fp){
        displayBST(avl->bst, fp);
        }

    void freeAVL(AVL *avl){
        freeBST(avl->bst);
        free(avl);
        }



/*PRIVATE functions for Fixing the AVL tree balance*/
    static void AVLinsertFixUp(AVL *avl, BSTNODE *fixNode){
        while(1){
            AVLvalue *AVLv = getBSTNODEvalue(fixNode);
            //Is this node the favorite -> 1=yes, 0=no favorite, -1=sibling
            int isNodeFav = favSibling(fixNode);
            BSTNODE *p = getBSTNODEparent(fixNode);
            AVLvalue *AVLp = getBSTNODEvalue(p);
            if(compAVLvalue(getBSTNODEvalue(getBSTroot(avl->bst)), AVLv) == 0){
                return;
                }
            //Parent favors the sibling
            else if(AVLp->balance != 0 && isNodeFav == -1){
                setBalance(getBSTNODEparent(fixNode));
                return;
                }
            //Parent has no favorite
            else if (AVLp->balance == 0){
                setBalance(getBSTNODEparent(fixNode));
                fixNode = getBSTNODEparent(fixNode);
                //continue looping
                }
            //Parent favors the Node
            else{
                //set y = the favorite child of fixNode
                // & p = parent of fixNode
                BSTNODE *y = 0;
                if(getBSTNODEleft(fixNode) != 0 || getBSTNODEright(fixNode) != 0){
                    if(favChild(fixNode) == 1){
                        y = getBSTNODEleft(fixNode);
                        }
                    else{
                        y = getBSTNODEright(fixNode);
                        }
                    }
                //does y exist and is not p,fixNode,y linear
                if (y != 0 && isLinear(p,fixNode,y) == 0){
                    //rotate y to fixNode
                    rotateNode(avl, fixNode, y);
                    //rotate y to p
                    rotateNode(avl, p, y);
                    setBalance(fixNode);
                    setBalance(p);
                    setBalance(y);
                    }
                //y doesn't exist or isn't linear with p,x
                else{
                    //rotate fixNode to p
                    rotateNode(avl, p, fixNode);
                    setBalance(p);
                    setBalance(fixNode);
                    }
                return;
                }

            }
        }

    static void deletionFixUp(AVL *avl, BSTNODE *fixNode){
        AVLvalue *AVLv = getBSTNODEvalue(fixNode);
        AVLv->height = 0;
        while(1){
            AVLvalue *AVLv = getBSTNODEvalue(fixNode);
            BSTNODE *p = getBSTNODEparent(fixNode);
            AVLvalue *AVLp = getBSTNODEvalue(p);
            int isNodeFav = favSibling(fixNode);
    printf("p balance: %d\nisNodeFav: %d (1=yes)\n", AVLp->balance, isNodeFav);
    displayAVLvalue(AVLp,stdout);
            printf("\n");
    displayAVLvalue(AVLv,stdout);
            printf("\n");
            if(compAVLvalue(getBSTNODEvalue(getBSTroot(avl->bst)), AVLv) == 0){
    printf("DELETE - case 0\n");
                return;
                }
            //parent favors fixNode
            else if (favSibling(fixNode) == 1){       //case 1
    printf("DELETE - case 1\n");
                setBalance(p);
                fixNode = p;
                AVLv = getBSTNODEvalue(fixNode);
                p = getBSTNODEparent(fixNode);
                AVLp = getBSTNODEvalue(p);
                }
            //parent has no favorite
            else if (AVLp->balance == 0){
    printf("DELETE - case 2\n");
                //setBalance of parent
                setBalance(p);
                return;
                }
            //uhh else
            else{
                //z = sibling of fixNode
                BSTNODE *z = sibling(fixNode); //Might need to make these before while(1)
                BSTNODE *y = z;
                //y = the favorite child of z
                int side = favChild(z);
                if(side == 1){
    printf("DELETE - case 3\n");
                    y = getBSTNODEleft(z);
                    }
                else if(side == -1){
    printf("DELETE - case 4\n");
                    y = getBSTNODEright(z);
                    }
                //if there is no favorite or no children
                else{
    printf("DELETE - case 5\n");
                    y = 0;
                    }
                //if y exists && y,z,p are not linear
    printf("p is:   ");
    displayAVLvalue(AVLp,stdout);
    printf("\nz is:   ");
    displayAVLvalue(getBSTNODEvalue(z),stdout);
    printf("\ny is:   ");
    displayAVLvalue(getBSTNODEvalue(y),stdout);
    printf("\n");
                if (y != 0 && isLinear(p,z,y) == 0){
    printf("DELETE - case 6\n");
                    //rotate y to z
                    rotateNode(avl, z, y);
                    rotateNode(avl, p, y);
                    //set the balances
                    setBalance(p);
                    setBalance(z);
                    setBalance(y);
                    //fixNode = y
                    fixNode = y;
                    AVLv = getBSTNODEvalue(fixNode);
                    p = getBSTNODEparent(fixNode);
                    AVLp = getBSTNODEvalue(p);
                    //continue looping
                    }
                else{
    printf("DELETE - case 7\n");
                    //rotate z to p                      //case 4
                    rotateNode(avl, p, z);
                    //set the balances
                    setBalance(p);
                    setBalance(z);
                    if (y == 0){
                        return;
                        }
                    fixNode = z;
                    AVLv = getBSTNODEvalue(fixNode);
                    p = getBSTNODEparent(fixNode);
                    AVLp = getBSTNODEvalue(p);
                    //continue looping
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
            AVLv->lheight = getAVLvalueHeight(getBSTNODEvalue(leftNode));
            }
        else{
            AVLv->lheight = 0;
            }
        //set right height
        if(rightNode != 0){
            AVLv->rheight = getAVLvalueHeight(getBSTNODEvalue(rightNode));
            }
        else{AVLv->rheight = 0;};
        //set total height
        if(AVLv->lheight >= AVLv->rheight){
            AVLv->height = AVLv->lheight + 1;
            }
        else{
            AVLv->height = AVLv->rheight + 1;
            }
        //set balance
        AVLv->balance = AVLv->lheight - AVLv->rheight;
        return AVLv->balance;
        }

    static BSTNODE *sibling(BSTNODE *checkNode){
        AVLvalue *AVLcheck = getBSTNODEvalue(checkNode);
        BSTNODE *checkP = getBSTNODEparent(checkNode);
        if(getBSTNODEleft(checkP) == 0){
            return 0;
            }
        else if(getBSTNODEright(checkP) == 0){
            return 0;
            }
        else if( compAVLvalue(getBSTNODEvalue(getBSTNODEleft(checkP)), AVLcheck) == 0){
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

    //Is this node the favorite -> 1=yes, 0=no favorite, -1=sibling, 2=root
    static int favSibling(BSTNODE *Node){
        BSTNODE *NodeSibling = sibling(Node);
        if(NodeSibling != 0){
            AVLvalue *AVLsib = getBSTNODEvalue(NodeSibling);
            AVLvalue *AVLnode = getBSTNODEvalue(Node);
            BSTNODE *par = getBSTNODEparent(Node);
            AVLvalue *AVLpar = getBSTNODEvalue(par);
            if(AVLpar->balance == 1 && compAVLvalue(AVLsib,getBSTNODEvalue(getBSTNODEleft(par))) == 0){
                return -1;
                }
            else if(AVLpar->balance == -1 && compAVLvalue(AVLsib,getBSTNODEvalue(getBSTNODEright(par))) == 0){
                return -1;
                }
            else if(AVLpar->balance != 0){
                return 1;
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
                if(getBSTNODEleft(x) != 0){
                    if(compAVLvalue(getBSTNODEvalue(getBSTNODEleft(x)),AVLy) == 0){
                        return 1;
                        }
                    else{return 0;}
                    }
                else{
                    return 0;
                    }
                }
            //is x to the right
            if(compAVLvalue(getBSTNODEvalue(getBSTNODEleft(p)), AVLx) == 0){
                if(getBSTNODEright(x) != 0){
                    if(compAVLvalue(getBSTNODEvalue(getBSTNODEright(x)),AVLy) == 0){
                        return 1;
                        }
                    else{return 0;}
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
    static void rotateNode(AVL *avl, BSTNODE *Node1, BSTNODE *Node2){
        //make sure these nodes are connected
        assert(isRight(Node1, Node2) != 0 || isLeft(Node1, Node2) != 0);
        BSTNODE *temp = getBSTNODEparent(Node1);
        if(isRight(Node1, Node2)){
            //check to see if Node1 is the root
            if(compAVLvalue(getBSTNODEvalue(temp), getBSTNODEvalue(Node1)) == 0){
                setBSTNODEparent(Node1, Node2);
                setBSTNODEparent(Node2, Node2);
                setBSTroot(avl->bst, Node2);
                }
            else{
                //Check to see if Node1 is its parents left or right
                if(isRight(temp, Node1)){
                    setBSTNODEright(temp, Node2);
                    }
                else{
                    setBSTNODEleft(temp, Node2);
                    }
                setBSTNODEparent(Node1, Node2);
                setBSTNODEparent(Node2, temp);
                }
            setBSTNODEright(Node1, getBSTNODEleft(Node2));
            if(getBSTNODEleft(Node2) != 0){
                setBSTNODEparent(getBSTNODEleft(Node2),Node1);
                }
            setBSTNODEleft(Node2, Node1);
            return;
            }
        else{
            //is root
            if(compAVLvalue(getBSTNODEvalue(temp), getBSTNODEvalue(Node1)) == 0){
                setBSTNODEparent(Node1, Node2);
                setBSTNODEparent(Node2, Node2);
                setBSTroot(avl->bst, Node2);
                }
            else{
                //Check to see if Node1 is its parents left or right
                if(isRight(temp, Node1)){
                    setBSTNODEright(temp, Node2);
                    }
                else{
                    setBSTNODEleft(temp, Node2);
                    }
                setBSTNODEparent(Node1, Node2);
                setBSTNODEparent(Node2, temp);
                }
            setBSTNODEleft(Node1, getBSTNODEright(Node2));
            if(getBSTNODEright(Node2) != 0){
                setBSTNODEparent(getBSTNODEright(Node2),Node1);
                }
            setBSTNODEright(Node2, Node1);
            return;
            }
        }
