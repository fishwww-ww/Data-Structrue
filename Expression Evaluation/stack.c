#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

//共10个功能函数
//C结尾函数为对运算符操作的函数
//N结尾函数为对运算数操作的函数
void InitStackC(SqStackC *s);                                //操作符栈初始化函数
void InitStackN(SqStackN *s);                                //操作数栈初始化函数
void PushC(SqStackC *s,char e);                              //操作符栈入栈函数
void PushN(SqStackN *s,double e);                            //操作数栈入栈函数
void PopC(SqStackC *s,char *e);                              //操作符栈出栈函数
void PopN(SqStackN *s,double *e);                            //操作数栈出栈函数
char GetTopC(SqStackC s);                                    //取操作符栈栈顶元素函数
double GetTopN(SqStackN s);                                  //取操作数栈栈顶元素函数
char Precede(char theta1,char theta2);                       //判定操作符栈的栈顶元素与读入的操作符之间优先关系的函数
double Operate(double a,char theta,double b);                //进行二元运算的函数


//主函数
int main()
{
    SqStackC OPTR;                                           //操作符栈
    SqStackN OPND;                                           //操作数栈
    char ch,theta;
    int lastIsPoint=0;                                       //上一个字符是否是'.'
    int cntExpression=0;                                     //记录表达式个数
    int cntPoint=1;                                          //记录小数点后几位
    double a,b;
    double num=0;
    double result[maxsize]={0};                              //存储每个表达式的结果
    InitStackC(&OPTR);
    InitStackN(&OPND);
    PushC(&OPTR,'=');
    scanf("%c",&ch);
    while (ch!='=')
    {
        while (ch!='=' || GetTopC(OPTR)!='=')
        {
            //ch是操作数或小数点
            if((ch>='0' && ch<='9') || ch=='.')
            {
                if(ch=='.')
                {
                    lastIsPoint=1;
                    scanf("%c",&ch);
                }
                else
                {
                    //上一次输入的ch为'.'
                    if(lastIsPoint)
                    {
                        num=num+pow(0.1,cntPoint)*(ch-'0');                 
                        cntPoint++;
                        scanf("%c",&ch);
                    }
                    //上一次输入的ch不为'.'
                    else
                    {
                        num=num*10+ch-'0';                   //-'0'不可省略，否则会ch会转换成ASCII码值，远大于ch强制转换成double的值
                        scanf("%c",&ch);
                    }
                }
            }
            //ch是操作符
            else
            {
                //重置有关小数及小数位数处理的变量
                if(lastIsPoint)
                {
                    lastIsPoint=0;                        
                    cntPoint=1;                           
                }
                //之前有数字 
                if(num!=0.0)
                {                          
                    PushN(&OPND,num);
                    num=0.0;                                 //重置num
                }
                switch (Precede(GetTopC(OPTR),ch))
                {
                    case '<':
                        PushC(&OPTR,ch);
                        scanf("%c",&ch);
                        break;
                    case '>':
                        PopC(&OPTR,&theta);                  //弹出操作符
                        PopN(&OPND,&a);                      //弹出操作数
                        PopN(&OPND,&b);                      //弹出操作数
                        PushN(&OPND,Operate(a,theta,b));     //将运算结果压入opnd栈
                        break;
                    case '=':
                        PopC(&OPTR,&theta);
                        scanf("%c",&ch);
                        break;
                }
            }
        }                                                    //里层while
        result[cntExpression]=GetTopN(OPND);
        cntExpression++;
        scanf("%c",&ch);                                     //处理缓冲区的回车
        scanf("%c",&ch);                                     //输入ch
    }                                                        //外层while
    //输出各个表达的值
    for(int i=0;i<cntExpression;i++)
    {
        printf("%.2f\n",result[i]);
    }
    return 0;
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

//进行二元运算的函数
double Operate(double a,char theta,double b)
{
    switch (theta)
    {
        case '+':
            return a+b;
        case '-':
            return b-a;                                      //由于栈先入后出的特性，这里要调换a，b顺序
        case '*':
            return a*b;
        case '/':
            return b/a;                                      //由于栈先入后出的特性，这里要调换a，b顺序
    }
}