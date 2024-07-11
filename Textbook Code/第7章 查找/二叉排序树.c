#include <stdio.h>
#include <stdlib.h>
#define KeyType int
#define InfoType int
#define ENDFLAG 65535 

typedef struct 
{
    KeyType key;
    InfoType otherinfo;
}ElemType;

typedef struct BSTNode
{
    ElemType data;
    struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

//二叉排序树的递归查找
BSTree SearchBST(BSTree T, KeyType key)
{
    if(!T || key == T->data.key)
        return T;
    else if(key < T->data.key)
        return SearchBST(T->lchild, key);//在左子树继续查找
    else
        return SearchBST(T->rchild, key);//在右子树继续查找
}

//二叉排序树的插入
void InsertBST(BSTree *T, ElemType e)
{
    if(!T)//T为空时执行
    {
        BSTree S = (BSTree)malloc(sizeof(BSTNode));//为新结点分配空间
        S->data = e;//初始化新结点
        S->lchild = S->rchild = NULL;//初始化新结点
        *T = S;//将新结点赋给插入位置
    }
    else if(e.key < (*T)->data.key)
    {
        InsertBST((*T)->lchild, e);
    }
    else if(e.key > (*T)->data.key)
    {
        InsertBST((*T)->rchild, e);
    }
}

//二叉排序树的创建
void CreateBST(BSTree *T)
{
    *T = NULL;//先将二叉排序树初始化为空树
    ElemType e;
    scanf("%d", &e);
    while (e.key != ENDFLAG)//ENDFLAG为自定义常量，作为输入结束标志
    {
        InsertBST(*T, e);
        scanf("%d", &e);
    }
}

//二叉排序树的删除
void DeleteBST(BSTree *T, KeyType key)
{
    BSTree *p = T;
    BSTree *f = NULL;
/*---------------------while循环从根开始查找被删结点----------------------------------------*/
    while (*p)
    {
        if((*p)->data.key == key)
            break;
        f = p;//接下去要往后寻找p的子树，所以要保存p
        if((*p)->data.key > key)
            *p = (*p)->lchild;
        else
            *p = (*p)->rchild;
    }
    if(!(*p))//找不到被删结点则返回
        exit(0);
/*--------------------考虑被删结点的3种情况：左右子树均不为空、左为空、右为空---------------------------------------*/
    BSTree *q = p;//p将继续往下，此后q相当于p的双亲，f为p的祖父母
    if((*p)->lchild && (*p)->rchild)//被删结点的左右子树均不为空
    {
        BSTree s = (*p)->lchild;
        while (s->rchild)
        {
            *q = s;
            s = s->rchild;//向右到尽头，直到s为p的中序遍历的直接前驱，此时q为s的双亲且s为q的右子树，且s无右孩子，左孩子是否为空不影响
        }
        (*p)->data = s->data;//修改data域即可，不需移动指针域*p=s
        if(*q != *p)//p，q指向一样，即while循环执行过
            (*q)->rchild = s->lchild;
        else//p，q指向一样，即while循环没有执行
            (*q)->lchild = s->lchild;
        free(s);
        return ;
    }
    else if(!(*p)->rchild)//被删结点无右子树
    {
        (*p) = (*p)->lchild;
    }
    else if(!(*p)->lchild)//被删结点无左子树
    {
        (*p) = (*p)->rchild;
    }
/*--------------------将p所指子树挂到双亲结点对应位置---------------------------------------*/
    if(!(*f))//双亲结点为空，即被删结点为根结点
        *T = *p;
    else if(*q == (*f)->lchild)//被删结点是其双亲结点的左孩子
        (*f)->lchild = *p;//用被删结点的孩子（左右上一个判断语句已求出）代替被删结点
    else//被删结点是其双亲结点的右孩子
        (*f)->rchild = *p;//用被删结点的孩子（左右上一个判断语句已求出）代替被删结点
    free(q);
}