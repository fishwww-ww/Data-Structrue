#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TElemType int 
#define maxsize 100

//ʹ��˳��ջ����
typedef struct 
{
    char *base;
    char *top;
    int stacksize;
}SqStackC;                                                   //������ջ�ṹ������
typedef struct 
{
    double *base;
    double *top;
    int stacksize;
}SqStackN;                                                   //������ջ�ṹ������

//����������ʽ�洢
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;


void InitStackC(SqStackC *s);                                //������ջ��ʼ������
void InitStackN(SqStackN *s);                                //������ջ��ʼ������
void PushC(SqStackC *s,char e);                              //������ջ��ջ����
void PushN(SqStackN *s,double e);                            //������ջ��ջ����
void PopC(SqStackC *s,char *e);                              //������ջ��ջ����
void PopN(SqStackN *s,double *e);                            //������ջ��ջ����
char GetTopC(SqStackC s);                                    //ȡ������ջջ��Ԫ�غ���
double GetTopN(SqStackN s);                                  //ȡ������ջջ��Ԫ�غ���
char Precede(char theta1,char theta2);                       //�ж�������ջ��ջ��Ԫ�������Ĳ�����֮�����ȹ�ϵ�ĺ���




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
    SqStackN *EXPT;//��ջ
    SqStackC *OPTR;//��ջ
    InitStackN(EXPT);
    InitStackC(OPTR);
    PushC(OPTR,'#');
    char ch;
    char theta;
    char a, b, x;
    scanf("%c", &ch);
    while (ch != '#' || GetTopC(&OPTR) != '#');
    {
        if(!In(ch));//ch���������
        {
            CreateExpTree(T, NULL, NULL, ch);//��chΪ������һ��ֻ�и����Ķ�����
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
                CreateExpTree(T, a, b, theta);//��thetaΪ����aΪ��������bΪ������������һ�Ŷ�����
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














//������ջ��ʼ������
void InitStackC(SqStackC *s)
{
    s->base=(char *)malloc(sizeof(char));
    if(!s->base){
        exit(0);
    }
    s->top=s->base;
    s->stacksize=maxsize;
}

//������ջ��ʼ������
void InitStackN(SqStackN *s)
{
    s->base=(double *)malloc(sizeof(double));
    if(!s->base){
        exit(0);
    }
    s->top=s->base;
    s->stacksize=maxsize;
}

//������ջ��ջ����
void PushC(SqStackC *s,char e)
{
    if(s->top-s->base==s->stacksize){
        exit(0);
    }
    *(s->top)=e;
    s->top++;
}

//������ջ��ջ����
void PushN(SqStackN *s,double e)
{
    if(s->top-s->base==s->stacksize){
        exit(0);
    }
    *(s->top)=e;
    s->top++;
}

//������ջ��ջ����
void PopC(SqStackC *s,char *e)
{
    if(s->top==s->base){
        exit(0);
    }
    s->top--;
    *e=*(s->top);
}

//������ջ��ջ����
void PopN(SqStackN *s,double *e)
{
    if(s->top==s->base){
        exit(0);
    }
    s->top--;
    *e=*(s->top);
}

//ȡ������ջջ��Ԫ�غ���
char GetTopC(SqStackC s)
{
    if(s.top!=s.base){
        return *(s.top-1);
    }
}

//ȡ������ջջ��Ԫ�غ���
double GetTopN(SqStackN s)
{
    if(s.top!=s.base){
        return *(s.top-1);
    }
}

//�ж�������ջ��ջ��Ԫ�������Ĳ�����֮�����ȹ�ϵ�ĺ���
char Precede(char theta1,char theta2)
{
    if((theta1=='(' && theta2==')') || (theta1=='=' && theta2=='='))
        return '=';
    else if(theta1=='(' || theta1=='=' || theta2=='(' || ((theta1=='+' || theta1=='-') && (theta2=='*' || theta2=='/')))
        return '<';
    else
        return '>';
}