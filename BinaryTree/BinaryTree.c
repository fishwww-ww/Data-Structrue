#include <stdio.h>
#include <stdlib.h>
#define maxsize 100

//  二叉树的链式存储
typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//  栈的顺序存储
typedef struct 
{
    BiTree *base;
    BiTree *top;
    int stacksize;
}SqStackN;   //  结点栈结构体类型
typedef struct 
{
    char *base;
    char *top;
    int stacksize;
}SqStackC;   //  操作符栈结构体类型


/*-----------树函数-------------*/
void InitExpTree(BiTree *T);
void CreateExpTree(BiTree *T, BiTree a, BiTree b, char theta);
int EvaluateExpTree(BiTree T);
/*----------操作函数------------*/
int GetValue(char data, int lvalue, int rvalue);
char Precede(char theta1,char theta2);
int In(char ch);
/*-----------栈函数------------*/
void InitStackN(SqStackN *s);
void PushN(SqStackN *s,BiTree e);
void PopN(SqStackN *s,BiTree *e);
void InitStackC(SqStackC *s);
void PushC(SqStackC *s,char e);
void PopC(SqStackC *s,char *e);
char GetTopC(SqStackC s);


//程序主函数
int main()
{
    BiTree T = NULL;                                    
    InitExpTree(&T);
}

//表达式树的创建算法
void InitExpTree(BiTree *T)
{
    SqStackN EXPT;                                     // 结点栈
    SqStackC OPTR;                                     // 符号栈
    InitStackN(&EXPT);
    InitStackC(&OPTR);
    PushC(&OPTR, '=');                                 // 压入'='进符号栈
    char ch;
    char theta;
    BiTree a, b;
    a = (BiTree)malloc(sizeof(BiTNode));
    b = (BiTree)malloc(sizeof(BiTNode));
    printf("请输入:");
    scanf("%c", &ch);
    while (ch != '=')
    {
        while (ch != '=' || GetTopC(OPTR) != '=')
        {
            if (!In(ch))                               //  ch不是运算符，是操作数
            {
                CreateExpTree(T, NULL, NULL, ch);      //  以ch为根创建一颗只有根结点的二叉树
                PushN(&EXPT, *T);                      //  将创建的树压入结点栈
                scanf("%c", &ch);
            }
            else                                       // ch是运算符
            {
                switch (Precede(GetTopC(OPTR), ch))
                {
                    case '<':
                        PushC(&OPTR, ch);
                        scanf("%c", &ch);
                        break;
                    case '>':
                        PopC(&OPTR, &theta);
                        PopN(&EXPT, &b);               //  根据栈的特性，先弹出b再弹出a
                        PopN(&EXPT, &a);
                        CreateExpTree(T, a, b, theta); //  以theta为根结点，a，b为左右子树
                        PushN(&EXPT, *T);              //  将新树的根节点入栈
                        break;
                    case '=':
                        PopC(&OPTR, &theta);           // 弹出'='
                        scanf("%c", &ch);
                        break;
                }
            }
        }
        printf("结果为:%d\n", EvaluateExpTree(*T));    //  计算结果并输出       
        getchar();                                    //  处理缓冲区
        printf("请输入:");
        scanf("%c", &ch);
    }
}

//创建表达式树
void CreateExpTree(BiTree *T, BiTree a, BiTree b, char theta)
{
    *T = (BiTree)malloc(sizeof(BiTNode));
    (*T)->data = theta;                                //  以theta为根
    (*T)->lchild = a;                                  //  a为左子树
    (*T)->rchild = b;                                  //  b为右子树
}

//遍历表达式树进行表达式求值
int EvaluateExpTree(BiTree T)
{
    int lvalue = 0;
    int rvalue = 0;
    if(T->lchild == NULL && T->lchild == NULL)         //  结点为操作数，则返回值
    {
        return T->data - '0';
    }
    else
    {
        lvalue = EvaluateExpTree(T->lchild);           //  递归求左子树的值
        rvalue = EvaluateExpTree(T->rchild);           //  递归求右子树的值
        return GetValue(T->data, lvalue, rvalue);
    }
}

//根据当前结点的运算符类型求值
int GetValue(char data, int lvalue, int rvalue)
{
    switch (data)
    {
        case '+':
            return lvalue + rvalue;
        case '-':
            return lvalue - rvalue;
        case '*':
            return lvalue * rvalue;
        case '/':
            return lvalue / rvalue;
    }
    return 0;
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

//判断是不是操作符
int In(char ch)
{
    if(ch >= '0' && ch <= '9')   //  不是运算符
        return 0;
    else                         //  是运算符
        return 1;
}

//结点栈初始化函数
void InitStackN(SqStackN *s)
{
    s->base=(BiTree *)malloc(sizeof(BiTree));
    if(!s->base){
        exit(0);
    }
    s->top=s->base;
    s->stacksize=maxsize;
}

//结点栈入栈函数
void PushN(SqStackN *s,BiTree e)
{
    if(s->top - s->base == s->stacksize){
        exit(0);
    }
    *(s->top) = e;
    s->top++;
}

//结点栈出栈函数
void PopN(SqStackN *s,BiTree *e)
{
    if(s->top == s->base){
        exit(0);
    }
    s->top--;
    *e = *(s->top);
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

//操作符栈入栈函数
void PushC(SqStackC *s,char e)
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

//取操作符栈栈顶元素函数
char GetTopC(SqStackC s)
{
    if(s.top!=s.base){
        return *(s.top-1);
    }
}