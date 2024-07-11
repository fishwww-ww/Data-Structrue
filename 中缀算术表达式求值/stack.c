#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

//��10�����ܺ���
//C��β����Ϊ������������ĺ���
//N��β����Ϊ�������������ĺ���
void InitStackC(SqStackC *s);                                //������ջ��ʼ������
void InitStackN(SqStackN *s);                                //������ջ��ʼ������
void PushC(SqStackC *s,char e);                              //������ջ��ջ����
void PushN(SqStackN *s,double e);                            //������ջ��ջ����
void PopC(SqStackC *s,char *e);                              //������ջ��ջ����
void PopN(SqStackN *s,double *e);                            //������ջ��ջ����
char GetTopC(SqStackC s);                                    //ȡ������ջջ��Ԫ�غ���
double GetTopN(SqStackN s);                                  //ȡ������ջջ��Ԫ�غ���
char Precede(char theta1,char theta2);                       //�ж�������ջ��ջ��Ԫ�������Ĳ�����֮�����ȹ�ϵ�ĺ���
double Operate(double a,char theta,double b);                //���ж�Ԫ����ĺ���


//������
int main()
{
    SqStackC OPTR;                                           //������ջ
    SqStackN OPND;                                           //������ջ
    char ch,theta;
    int lastIsPoint=0;                                       //��һ���ַ��Ƿ���'.'
    int cntExpression=0;                                     //��¼���ʽ����
    int cntPoint=1;                                          //��¼С�����λ
    double a,b;
    double num=0;
    double result[maxsize]={0};                              //�洢ÿ�����ʽ�Ľ��
    InitStackC(&OPTR);
    InitStackN(&OPND);
    PushC(&OPTR,'=');
    scanf("%c",&ch);
    while (ch!='=')
    {
        while (ch!='=' || GetTopC(OPTR)!='=')
        {
            //ch�ǲ�������С����
            if((ch>='0' && ch<='9') || ch=='.')
            {
                if(ch=='.')
                {
                    lastIsPoint=1;
                    scanf("%c",&ch);
                }
                else
                {
                    //��һ�������chΪ'.'
                    if(lastIsPoint)
                    {
                        num=num+pow(0.1,cntPoint)*(ch-'0');                 
                        cntPoint++;
                        scanf("%c",&ch);
                    }
                    //��һ�������ch��Ϊ'.'
                    else
                    {
                        num=num*10+ch-'0';                   //-'0'����ʡ�ԣ������ch��ת����ASCII��ֵ��Զ����chǿ��ת����double��ֵ
                        scanf("%c",&ch);
                    }
                }
            }
            //ch�ǲ�����
            else
            {
                //�����й�С����С��λ������ı���
                if(lastIsPoint)
                {
                    lastIsPoint=0;                        
                    cntPoint=1;                           
                }
                //֮ǰ������ 
                if(num!=0.0)
                {                          
                    PushN(&OPND,num);
                    num=0.0;                                 //����num
                }
                switch (Precede(GetTopC(OPTR),ch))
                {
                    case '<':
                        PushC(&OPTR,ch);
                        scanf("%c",&ch);
                        break;
                    case '>':
                        PopC(&OPTR,&theta);                  //����������
                        PopN(&OPND,&a);                      //����������
                        PopN(&OPND,&b);                      //����������
                        PushN(&OPND,Operate(a,theta,b));     //��������ѹ��opndջ
                        break;
                    case '=':
                        PopC(&OPTR,&theta);
                        scanf("%c",&ch);
                        break;
                }
            }
        }                                                    //���while
        result[cntExpression]=GetTopN(OPND);
        cntExpression++;
        scanf("%c",&ch);                                     //���������Ļس�
        scanf("%c",&ch);                                     //����ch
    }                                                        //���while
    //�����������ֵ
    for(int i=0;i<cntExpression;i++)
    {
        printf("%.2f\n",result[i]);
    }
    return 0;
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

//���ж�Ԫ����ĺ���
double Operate(double a,char theta,double b)
{
    switch (theta)
    {
        case '+':
            return a+b;
        case '-':
            return b-a;                                      //����ջ�����������ԣ�����Ҫ����a��b˳��
        case '*':
            return a*b;
        case '/':
            return b/a;                                      //����ջ�����������ԣ�����Ҫ����a��b˳��
    }
}