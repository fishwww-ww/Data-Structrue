#include<stdio.h>
#include<stdlib.h>
#define MAXTSIZE 100
#define MAXSIZE 100
#define TElemType int

//��������˳��洢��ʾ
typedef TElemType SqBiTree[MAXTSIZE];
SqBiTree bt;

//�������Ķ�����ʽ�洢��ʾ
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//˳��ջ
typedef struct 
{
    BiTNode *base;
    BiTNode *top;
    int stacksize;
}SqStack;

//˳��ջ��ʼ��
int InitStack(SqStack *s)
{
    s->base=(BiTNode *)malloc(sizeof(BiTNode));
    if(!s->base){
        exit(0);
    }
    s->top=s->base;
    s->stacksize=MAXSIZE;
    return 1;
}

//˳��ջ��ջ
int Push(SqStack *s,BiTNode e)
{
    if(s->top-s->base==s->stacksize){
        return 0;
    }
    *(s->top)=e;
    s->top++;
    return 1;
}

//˳��ջ��ջ
int Pop(SqStack *s,BiTNode *e)
{
    if(s->top==s->base){
        return 0;
    }
    s->top--;
    *e=*(s->top);
    return 1;
}

//�ж�ջ�Ƿ�Ϊ��
int StackEmpty(SqStack s)
{
    if(s.top-s.base==s.stacksize)
        return 0;
    else
        return 1;
}

//��������ĵݹ��㷨
void InOrderTraverse_1(BiTree T)
{
    if(T)
    {
        InOrderTraverse_1(T->lchild);
        printf("%c\n",T->data);
        InOrderTraverse_1(T->rchild);
    }
}

//��������ķǵݹ��㷨
//����������������
void InOrderTraverse_2(BiTree T)
{
    BiTree p=T;
    BiTNode q;
    SqStack S;
    InitStack(&S);
    while (p || !StackEmpty(S))
    {
        if(p)
        {
            Push(&S,*p);
            p=p->lchild;
        }
        else{
            Pop(&S,&q);
            printf("%c\n",q.data);
            p=q.rchild;
        }
    }
}

//�������������������н���ֵ�����ַ������������������ʾ�Ķ�����
void CreateBiTree(BiTree *T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
    {
        *T=NULL;
    }
    else
    {
        *T=(BiTree)malloc((sizeof(BiTNode)));
        (*T)->data=ch;
        CreateBiTree(&((*T)->lchild));
        CreateBiTree(&((*T)->rchild));
    }
}

//���ƶ�����
void Copy(BiTree T,BiTree *NewT)
{
    if(T==NULL)
    {
        exit(0);
    }
    else
    {
        *NewT=(BiTree)malloc(sizeof(BiTNode));
        (*NewT)->data=T->data;
        Copy(T->lchild,(*NewT)->lchild);
        Copy(T->rchild,(*NewT)->rchild);
    }
}

//��������������
int Depth(BiTree T)
{
    int m,n;
    if(T==NULL)
    {
        return 0;
    }
    else
    {
        m=Depth(T->lchild);
        n=Depth(T->rchild);
        if(m>n)
            return m+1;
        else
            return n+1;
    }
}

//ͳ�ƶ������н��ĸ���
int NodeCount(BiTree T)
{
    if(T==NULL)
        return 0;
    else
        return NodeCount(T->lchild)+NodeCount(T->rchild)+1;
} 

int main()
{
    BiTree T;
    CreateBiTree(&T);
    InOrderTraverse_2(T);
    return 0;
}