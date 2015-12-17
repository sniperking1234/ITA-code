/*********************************************
 * @chen
 * 红黑树插入删除操作
 * v1.0 按照算法导论书上伪代码
 * 没有注释，稍后添加
 * 2015-12-17
 *********************************************/


#include <stdio.h>
#include <stdlib.h>
enum COLOR
{
    BLACK,
    RED
};

typedef struct RBTreeNood
{
    struct RBTreeNood *lchild;
    struct RBTreeNood *rchild;
    struct RBTreeNood *parent;
    int color;
    int key;
} RBnood;

typedef struct RBTree
{
    RBnood *root;
    RBnood *nil;
} RBtree;

int LeftRotate(RBtree *tree, RBnood *xnode);
int RightRotate(RBtree *tree, RBnood *ynode);
int RBInsert(RBtree *tree, RBnood *newNode);
int RBInsertFixup(RBtree *tree, RBnood *z);

RBnood *TreeMinimum(RBnood *z, RBtree *tree);
int RBTransplant(RBtree *tree, RBnood *parentNode, RBnood *childNode);
int RBDelete(RBtree *tree, RBnood *z);
int RBDeleteFixup(RBtree *tree, RBnood *x);

void preOrder(RBtree *tree, RBnood *z);
void preOrderDelete(RBtree *tree, RBnood *z, int key);


int main()
{
    int option;
    int key;
    RBtree *tree = (RBtree *)malloc(sizeof(RBtree));
    tree->nil = (RBnood *)malloc(sizeof(RBnood));
    tree->nil->color = BLACK;

    RBnood *newNood ;
    tree->root = NULL;
    while (1)
    {
        printf("请选择操作\n1.添加节点2.删除节点3.显示红黑树\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            newNood = (RBnood *)malloc(sizeof(RBnood));
            printf("请输入key\n");
            scanf("%d", &key);
            newNood->key = key;
            newNood->lchild = tree->nil;
            newNood->rchild = tree->nil;
            newNood->parent = tree->nil;
            if (tree->root == NULL)
            {
                tree->root = newNood;
            }
            else
            {
                RBInsert(tree, newNood);
            }
            break;
        case 2:
            printf("请输入key\n");
            scanf("%d", &key);
            preOrderDelete(tree, tree->root, key);
            break;
        case 3:
            preOrder(tree, tree->root);
        }
    }
    return 0;
}

int LeftRotate(RBtree *tree, RBnood *xnode)
{
    RBnood * ynode = xnode ->rchild;
    xnode ->rchild = ynode ->lchild;
    if (ynode ->lchild != tree->nil)
    {
        ynode ->lchild ->parent = xnode;
    }
    ynode ->parent = xnode ->parent;
    if (xnode ->parent == tree->nil)
    {
        tree ->root = ynode;
    }
    else if (xnode == xnode ->parent ->lchild)
    {
        xnode ->parent ->lchild = ynode;
    }
    else
    {
        xnode ->parent ->rchild = ynode;
    }
    ynode ->lchild = xnode;
    xnode ->parent = ynode;
    return 0;
}

int RightRotate(RBtree *tree, RBnood *ynode)
{
    RBnood * xnode = ynode ->lchild;
    ynode ->lchild = xnode ->rchild;
    if (xnode ->rchild != tree->nil)
    {
        xnode ->rchild ->parent = ynode;
    }
    xnode ->parent = ynode ->parent;
    if (ynode ->parent == tree->nil)
    {
        tree ->root = xnode;
    }
    else if (ynode == ynode ->parent ->rchild)
    {
        ynode ->parent ->rchild = xnode;
    }
    else
    {
        ynode ->parent ->lchild = xnode;
    }
    xnode ->rchild = ynode;
    ynode ->parent = xnode;
    return 0;
}

int RBInsert(RBtree *tree, RBnood *newNode)
{
    RBnood *y = tree ->nil;
    RBnood *x = tree ->root;
    while (x != tree ->nil)
    {
        y = x;
        if (newNode ->key < x ->key)
        {
            x = x ->lchild;
        }
        else
        {
            x = x ->rchild;
        }
    }
    newNode ->parent = y;
    if (y == tree->nil)
    {
        tree ->root = newNode;
    }
    else if (newNode ->key < y ->key)
    {
        y ->lchild = newNode;
    }
    else
    {
        y ->rchild = newNode;
    }
    newNode ->lchild = tree ->nil;
    newNode ->rchild = tree ->nil;
    newNode ->parent = y;
    newNode ->color = RED;
    RBInsertFixup(tree, newNode);
    return 0;
}

int RBInsertFixup(RBtree *tree, RBnood *z)
{
    RBnood *y;
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->lchild)
        {
            y = z->parent->parent->rchild;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
                continue;
            }
            else if (z == z->parent->rchild)
            {
                z = z->parent;
                LeftRotate(tree, z);
            }
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            RightRotate(tree, z->parent->parent);
        }
        else
        {
            y = z->parent->parent->lchild;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
                continue;
            }
            else if (z == z->parent->lchild)
            {
                z = z->parent;
                RightRotate(tree, z);
            }
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            LeftRotate(tree, z->parent->parent);
        }
    tree->root->color = BLACK;
    }
    return 0;
}

int RBTransplant(RBtree *tree, RBnood *parentNode, RBnood *childNode)
{
    if (parentNode->parent == tree->nil)
    {
        tree->root = childNode;
    }
    else if (parentNode == parentNode->parent->lchild)
    {
        parentNode ->parent->lchild = childNode;
    }
    else
    {
        parentNode->parent->rchild = childNode;
    }
    childNode->parent = parentNode->parent;
    return 0;
}

int RBDelete(RBtree *tree, RBnood *z)
{
    RBnood *x;
    RBnood *y = z;
    int yOrigColor = y->color;
    if (z->lchild == tree->nil)
    {
        x = z->rchild;
        RBTransplant(tree, z, z->rchild);
    }
    else if (z->rchild == tree->nil)
    {
        x = z->lchild;
        RBTransplant(tree, z, z->lchild);
    }
    else
    {
        y = TreeMinimum(z->rchild, tree);
        yOrigColor = y->color;
        x = y->rchild;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            RBTransplant(tree, y, y->rchild);
            y->rchild = z->rchild;
            y->rchild->parent = y;
        }
        RBTransplant(tree, z, y);
        y->lchild = z->lchild;
        y->lchild->parent = y;
        y->color = z->color;
    }
    if (yOrigColor == BLACK)
    {
        RBDeleteFixup(tree, x);
    }
    return 0;
}

int RBDeleteFixup(RBtree *tree, RBnood *x)
{
    RBnood *w;
    while (x != tree->root && x->color == BLACK)
    {
        if (x == x->parent->lchild)
        {
            w = x->parent->rchild;
            if (w->color == RED)
            {
                w->color = BLACK;
                w->parent->color = RED;
                LeftRotate(tree, x->parent);
                w = x->parent->rchild;
            }
            if (w->lchild->color == BLACK && w->rchild->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
                continue;
            }
            else if (w->rchild->color == BLACK)
            {
                w->lchild->color = BLACK;
                w->color = RED;
                RightRotate(tree, w);
                w = x->parent->rchild;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->rchild->color = BLACK;
            LeftRotate(tree, x->parent);
            x = tree->root;
        }
        else
        {
            w = x->parent->lchild;
            if (w->color == RED)
            {
                w->color = BLACK;
                w->parent->color = RED;
                RightRotate(tree, x->parent);
                w = x->parent->lchild;
            }
            if (w->rchild->color == BLACK && w->lchild->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
                continue;
            }
            else if (w->lchild->color == BLACK)
            {
                w->rchild->color = BLACK;
                w->color = RED;
                LeftRotate(tree, w);
                w = x->parent->lchild;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->lchild->color = BLACK;
            RightRotate(tree, x->parent);
            x = tree->root;
        }
    }
    x->color = BLACK;
    return 0;
}

RBnood *TreeMinimum(RBnood *z, RBtree *tree)
{
    while(z->lchild!=tree->nil)
        z = z ->lchild;
    return z;
}

void preOrder(RBtree *tree, RBnood *z)
{
    if (z == tree->nil)
    {
        return;
    }
    printf("key is %d  color is %d\n", z->key, z->color);
    preOrder(tree, z->lchild);
    preOrder(tree, z->rchild);
}

void preOrderDelete(RBtree *tree, RBnood *z, int key)
{
    if (z == tree->nil)
        return;
    if(z->key == key)
        RBDelete(tree, z);
    preOrderDelete(tree, z->lchild,key);
    preOrderDelete(tree, z->rchild,key);
}
