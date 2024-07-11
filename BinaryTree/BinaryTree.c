#include <stdio.h>
#include <stdlib.h>
#define maxsize 100

//  ����������ʽ�洢
typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//  ջ��˳��洢
typedef struct 
{
    BiTree *base;
    BiTree *top;
    int stacksize;
}SqStackN;   //  ���ջ�ṹ������
typedef struct 
{
    char *base;
    char *top;
    int stacksize;
}SqStackC;   //  ������ջ�ṹ������


/*-----------������-------------*/
void InitExpTree(BiTree *T);
void CreateExpTree(BiTree *T, BiTree a, BiTree b, char theta);
int EvaluateExpTree(BiTree T);
/*----------��������------------*/
int GetValue(char data, int lvalue, int rvalue);
char Precede(char theta1,char theta2);
int In(char ch);
/*-----------ջ����------------*/
void InitStackN(SqStackN *s);
void PushN(SqStackN *s,BiTree e);
void PopN(SqStackN *s,BiTree *e);
void InitStackC(SqStackC *s);
void PushC(SqStackC *s,char e);
void PopC(SqStackC *s,char *e);
char GetTopC(SqStackC s);


//����������
int main()
{
    BiTree T = NULL;                                    
    InitExpTree(&T);
}

//���ʽ���Ĵ����㷨
void InitExpTree(BiTree *T)
{
    SqStackN EXPT;                                     // ���ջ
    SqStackC OPTR;                                     // ����ջ
    InitStackN(&EXPT);
    InitStackC(&OPTR);
    PushC(&OPTR, '=');                                 // ѹ��'='������ջ
    char ch;
    char theta;
    BiTree a, b;
    a = (BiTree)malloc(sizeof(BiTNode));
    b = (BiTree)malloc(sizeof(BiTNode));
    printf("������:");
    scanf("%c", &ch);
    while (ch != '=')
    {
        while (ch != '=' || GetTopC(OPTR) != '=')
        {
            if (!In(ch))                               //  ch������������ǲ�����
            {
                CreateExpTree(T, NULL, NULL, ch);      //  ��chΪ������һ��ֻ�и����Ķ�����
                PushN(&EXPT, *T);                      //  ����������ѹ����ջ
                scanf("%c", &ch);
            }
            else                                       // ch�������
            {
                switch (Precede(GetTopC(OPTR), ch))
                {
                    case '<':
                        PushC(&OPTR, ch);
                        scanf("%c", &ch);
                        break;
                    case '>':
                        PopC(&OPTR, &theta);
                        PopN(&EXPT, &b);               //  ����ջ�����ԣ��ȵ���b�ٵ���a
                        PopN(&EXPT, &a);
                        CreateExpTree(T, a, b, theta); //  ��thetaΪ����㣬a��bΪ��������
                        PushN(&EXPT, *T);              //  �������ĸ��ڵ���ջ
                        break;
                    case '=':
                        PopC(&OPTR, &theta);           // ����'='
                        scanf("%c", &ch);
                        break;
                }
            }
        }
        printf("���Ϊ:%d\n", EvaluateExpTree(*T));    //  �����������       
        getchar();                                    //  ��������
        printf("������:");
        scanf("%c", &ch);
    }
}

//�������ʽ��
void CreateExpTree(BiTree *T, BiTree a, BiTree b, char theta)
{
    *T = (BiTree)malloc(sizeof(BiTNode));
    (*T)->data = theta;                                //  ��thetaΪ��
    (*T)->lchild = a;                                  //  aΪ������
    (*T)->rchild = b;                                  //  bΪ������
}

//�������ʽ�����б��ʽ��ֵ
int EvaluateExpTree(BiTree T)
{
    int lvalue = 0;
    int rvalue = 0;
    if(T->lchild == NULL && T->lchild == NULL)         //  ���Ϊ���������򷵻�ֵ
    {
        return T->data - '0';
    }
    else
    {
        lvalue = EvaluateExpTree(T->lchild);           //  �ݹ�����������ֵ
        rvalue = EvaluateExpTree(T->rchild);           //  �ݹ�����������ֵ
        return GetValue(T->data, lvalue, rvalue);
    }
}

//���ݵ�ǰ���������������ֵ
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

//�ж��ǲ��ǲ�����
int In(char ch)
{
    if(ch >= '0' && ch <= '9')   //  ���������
        return 0;
    else                         //  �������
        return 1;
}

//���ջ��ʼ������
void InitStackN(SqStackN *s)
{
    s->base=(BiTree *)malloc(sizeof(BiTree));
    if(!s->base){
        exit(0);
    }
    s->top=s->base;
    s->stacksize=maxsize;
}

//���ջ��ջ����
void PushN(SqStackN *s,BiTree e)
{
    if(s->top - s->base == s->stacksize){
        exit(0);
    }
    *(s->top) = e;
    s->top++;
}

//���ջ��ջ����
void PopN(SqStackN *s,BiTree *e)
{
    if(s->top == s->base){
        exit(0);
    }
    s->top--;
    *e = *(s->top);
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
void PopC(SqStackC *s,char *e)
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