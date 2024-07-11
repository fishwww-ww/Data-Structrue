#include<stdio.h>
#include<stdlib.h>
#define TElemType int

//二叉树的二叉线索存储表示
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lchild,*rchild;
    int LTag,RTag;
}BiThrNode,*BiThrTree;

//以结点p为根的子树中序线索化
void InThreading(BiThrTree p)
{
    BiThrNode *pre=(BiThrNode *)malloc(sizeof(BiThrNode));
    if(p)
    {
        InThreading(p->lchild);
        if(!p->lchild)
        {
            p->LTag=1;
            p->lchild=pre;
        }
        else
        {
            p->LTag=0;
        }
        if(!pre->rchild)
        {
            pre->RTag=1;
            pre->rchild=p;
        }
        else
        {
            pre->RTag=0;
        }
        pre=p;
        InThreading(p->rchild);
    }
    
}

//带头结点的二叉树中序线索化
void InOrderThreading(BiThrTree *Thrt,BiThrTree T)
{
    BiThrNode *pre=(BiThrNode *)malloc(sizeof(BiThrNode));
    (*Thrt)->LTag=0;
    (*Thrt)->RTag=1;
    (*Thrt)->rchild=Thrt;
    if(!T)
    {
        (*Thrt)->lchild=Thrt;
    }
    else
    {
        (*Thrt)->lchild=T;
        pre=Thrt;
        InThreading(T);
        pre->RTag=1;
        (*Thrt)->rchild=pre;
    }
}