#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TElemType int 
#define maxsize 100

//使用顺序栈定义
typedef struct 
{
    char *base;
    char *top;
    int stacksize;
}SqStackC;                                                   //操作符栈结构体类型
typedef struct 
{
    double *base;
    double *top;
    int stacksize;
}SqStackN;                                                   //操作数栈结构体类型

//二叉树的链式存储
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;


void InitStackC(SqStackC *s);                                //操作符栈初始化函数
void InitStackN(SqStackN *s);                                //操作数栈初始化函数
void PushC(SqStackC *s,char e);                              //操作符栈入栈函数
void PushN(SqStackN *s,double e);                            //操作数栈入栈函数
void PopC(SqStackC *s,char *e);                              //操作符栈出栈函数
void PopN(SqStackN *s,double *e);                            //操作数栈出栈函数
char GetTopC(SqStackC s);                                    //取操作符栈栈顶元素函数
double GetTopN(SqStackN s);                                  //取操作数栈栈顶元素函数
char Precede(char theta1,char theta2);                       //判定操作符栈的栈顶元素与读入的操作符之间优先关系的函数




int EvaluateExpTree(BiTree T)
{
    int lvalue = 0;
    int rvalue = 0;
    if(T->lchild = NULL && T->lchild = NULL)
    {
        return T->data - '0';
    }
    else
    {
        lvalue = EvaluateExpTree(T->lchild);
        rvalue = EvaluateExpTree(T->rchild);
        return GetValue(T->data, lvalue, rvalue);
    }
}

void InitExpTree()
{
    SqStackN *EXPT;//数栈
    SqStackC *OPTR;//符栈
    InitStackN(EXPT);
    InitStackC(OPTR);
    PushC(OPTR,'#');
    char ch;
    char theta;
    char a, b, x;
    scanf("%c", &ch);
    while (ch != '#' || GetTopC(&OPTR) != '#');
    {
        if(!In(ch));//ch不是运算符
        {
            CreateExpTree(T, NULL, NULL, ch);//以ch为根创建一颗只有根结点的二叉树
            Push(EXPT, T);
            scanf("%c", &ch);
        }
        else
        {
            switch (Precede(GetTop(OPTR)), ch)
            {
            case '<':
                PushC(OPTR, ch);
                scanf("%c", &ch);
                break;
            case '>':
                PopC(OPTR, theta);
                PopN(EXPT, b);
                PopN(EXPT, a);
                CreateExpTree(T, a, b, theta);//以theta为根，a为左子树，b为右子树，创建一颗二叉树
                PushN(EXPT, T);
                break;
            case '=':
                PopC(OPTR, x);
                scanf("%c", &ch);
                break;
            }
        }
    }
}














//操作符栈初始化函数
void InitStackC(SqStackC *s)
{
    s->base=(char *)malloc(sizeof(char));
    if(!s->base){
        exit(0);
    }
    s->top=s->base;
    s->stacksize=maxsize;
}

//操作数栈初始化函数
void InitStackN(SqStackN *s)
{
    s->base=(double *)malloc(sizeof(double));
    if(!s->base){
        exit(0);
    }
    s->top=s->base;
    s->stacksize=maxsize;
}

//操作符栈入栈函数
void PushC(SqStackC *s,char e)
{
    if(s->top-s->base==s->stacksize){
        exit(0);
    }
    *(s->top)=e;
    s->top++;
}

//操作数栈入栈函数
void PushN(SqStackN *s,double e)
{
    if(s->top-s->base==s->stacksize){
        exit(0);
    }
    *(s->top)=e;
    s->top++;
}

//操作符栈出栈函数
void PopC(SqStackC *s,char *e)
{
    if(s->top==s->base){
        exit(0);
    }
    s->top--;
    *e=*(s->top);
}

//操作数栈出栈函数
void PopN(SqStackN *s,double *e)
{
    if(s->top==s->base){
        exit(0);
    }
    s->top--;
    *e=*(s->top);
}

//取操作符栈栈顶元素函数
char GetTopC(SqStackC s)
{
    if(s.top!=s.base){
        return *(s.top-1);
    }
}

//取操作数栈栈顶元素函数
double GetTopN(SqStackN s)
{
    if(s.top!=s.base){
        return *(s.top-1);
    }
}

//判定操作符栈的栈顶元素与读入的操作符之间优先关系的函数
char Precede(char theta1,char theta2)
{
    if((theta1=='(' && theta2==')') || (theta1=='=' && theta2=='='))
        return '=';
    else if(theta1=='(' || theta1=='=' || theta2=='(' || ((theta1=='+' || theta1=='-') && (theta2=='*' || theta2=='/')))
        return '<';
    else
        return '>';
}