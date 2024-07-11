#include<stdio.h>
#include<stdlib.h>
#define MAXTSIZE 100
#define MAXSIZE 100
#define TElemType int

//二叉树的顺序存储表示
typedef TElemType SqBiTree[MAXTSIZE];
SqBiTree bt;

//二叉树的二叉链式存储表示
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//顺序栈
typedef struct 
{
    BiTNode *base;
    BiTNode *top;
    int stacksize;
}SqStack;

//顺序栈初始化
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

//顺序栈入栈
int Push(SqStack *s,BiTNode e)
{
    if(s->top-s->base==s->stacksize){
        return 0;
    }
    *(s->top)=e;
    s->top++;
    return 1;
}

//顺序栈出栈
int Pop(SqStack *s,BiTNode *e)
{
    if(s->top==s->base){
        return 0;
    }
    s->top--;
    *e=*(s->top);
    return 1;
}

//判断栈是否为空
int StackEmpty(SqStack s)
{
    if(s.top-s.base==s.stacksize)
        return 0;
    else
        return 1;
}

//中序遍历的递归算法
void InOrderTraverse_1(BiTree T)
{
    if(T)
    {
        InOrderTraverse_1(T->lchild);
        printf("%c\n",T->data);
        InOrderTraverse_1(T->rchild);
    }
}

//中序遍历的非递归算法
//各个函数都有问题
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

//按先序次序输入二叉树中结点的值（单字符），创建二叉链表表示的二叉树
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

//复制二叉树
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

//计算二叉树的深度
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

//统计二叉树中结点的个数
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