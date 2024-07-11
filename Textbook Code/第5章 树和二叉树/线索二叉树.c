#include<stdio.h>
#include<stdlib.h>
#define TElemType int

//�������Ķ��������洢��ʾ
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lchild,*rchild;
    int LTag,RTag;
}BiThrNode,*BiThrTree;

//�Խ��pΪ������������������
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

//��ͷ���Ķ���������������
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