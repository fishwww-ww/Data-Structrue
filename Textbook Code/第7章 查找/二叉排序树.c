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

//�����������ĵݹ����
BSTree SearchBST(BSTree T, KeyType key)
{
    if(!T || key == T->data.key)
        return T;
    else if(key < T->data.key)
        return SearchBST(T->lchild, key);//����������������
    else
        return SearchBST(T->rchild, key);//����������������
}

//�����������Ĳ���
void InsertBST(BSTree *T, ElemType e)
{
    if(!T)//TΪ��ʱִ��
    {
        BSTree S = (BSTree)malloc(sizeof(BSTNode));//Ϊ�½�����ռ�
        S->data = e;//��ʼ���½��
        S->lchild = S->rchild = NULL;//��ʼ���½��
        *T = S;//���½�㸳������λ��
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

//�����������Ĵ���
void CreateBST(BSTree *T)
{
    *T = NULL;//�Ƚ�������������ʼ��Ϊ����
    ElemType e;
    scanf("%d", &e);
    while (e.key != ENDFLAG)//ENDFLAGΪ�Զ��峣������Ϊ���������־
    {
        InsertBST(*T, e);
        scanf("%d", &e);
    }
}

//������������ɾ��
void DeleteBST(BSTree *T, KeyType key)
{
    BSTree *p = T;
    BSTree *f = NULL;
/*---------------------whileѭ���Ӹ���ʼ���ұ�ɾ���----------------------------------------*/
    while (*p)
    {
        if((*p)->data.key == key)
            break;
        f = p;//����ȥҪ����Ѱ��p������������Ҫ����p
        if((*p)->data.key > key)
            *p = (*p)->lchild;
        else
            *p = (*p)->rchild;
    }
    if(!(*p))//�Ҳ�����ɾ����򷵻�
        exit(0);
/*--------------------���Ǳ�ɾ����3�������������������Ϊ�ա���Ϊ�ա���Ϊ��---------------------------------------*/
    BSTree *q = p;//p���������£��˺�q�൱��p��˫�ף�fΪp���游ĸ
    if((*p)->lchild && (*p)->rchild)//��ɾ����������������Ϊ��
    {
        BSTree s = (*p)->lchild;
        while (s->rchild)
        {
            *q = s;
            s = s->rchild;//���ҵ���ͷ��ֱ��sΪp�����������ֱ��ǰ������ʱqΪs��˫����sΪq������������s���Һ��ӣ������Ƿ�Ϊ�ղ�Ӱ��
        }
        (*p)->data = s->data;//�޸�data�򼴿ɣ������ƶ�ָ����*p=s
        if(*q != *p)//p��qָ��һ������whileѭ��ִ�й�
            (*q)->rchild = s->lchild;
        else//p��qָ��һ������whileѭ��û��ִ��
            (*q)->lchild = s->lchild;
        free(s);
        return ;
    }
    else if(!(*p)->rchild)//��ɾ�����������
    {
        (*p) = (*p)->lchild;
    }
    else if(!(*p)->lchild)//��ɾ�����������
    {
        (*p) = (*p)->rchild;
    }
/*--------------------��p��ָ�����ҵ�˫�׽���Ӧλ��---------------------------------------*/
    if(!(*f))//˫�׽��Ϊ�գ�����ɾ���Ϊ�����
        *T = *p;
    else if(*q == (*f)->lchild)//��ɾ�������˫�׽�������
        (*f)->lchild = *p;//�ñ�ɾ���ĺ��ӣ�������һ���ж��������������汻ɾ���
    else//��ɾ�������˫�׽����Һ���
        (*f)->rchild = *p;//�ñ�ɾ���ĺ��ӣ�������һ���ж��������������汻ɾ���
    free(q);
}