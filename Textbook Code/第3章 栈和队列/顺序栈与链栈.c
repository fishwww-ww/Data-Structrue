#include <stdio.h>
#include <stdlib.h>
#define maxsize 100

// //˳��ջ
// typedef struct 
// {
//     int *base;
//     int *top;
//     int stacksize;
// }SqStack;

// //˳��ջ��ʼ��
// int InitStack(SqStack *s)
// {
//     s->base=(int *)malloc(sizeof(int));
//     if(!s->base){
//         exit(0);
//     }
//     s->top=s->base;
//     s->stacksize=maxsize;
//     return 1;
// }

// //˳��ջ��ջ
// int Push(SqStack *s,int e)
// {
//     if(s->top-s->base==s->stacksize){
//         return 0;
//     }
//     *(s->top)=e;
//     s->top++;
//     return 1;
// }

// //˳��ջ��ջ
// int Pop(SqStack *s,int *e)
// {
//     if(s->top==s->base){
//         return 0;
//     }
//     s->top--;
//     *e=*(s->top);
//     return 1;
// }

// //ȡ˳��ջջ��Ԫ��
// int GetTop(SqStack s)
// {
//     if(s.top!=s.base){
//         return *(s.top-1);
//     }
// }



//��ջ
typedef struct StackNode
{
    int data;
    struct StackNode *next;
}StackNode,*LinkStack;

//��ջ��ʼ��
int InitStack(LinkStack *s)
{
    *s=NULL;  //*s=NULL;
    return 1;
}

//��ջ��ջ
int Push(LinkStack *s,int e)
{
    StackNode *p=(StackNode *)malloc(sizeof(StackNode));
    p->data=e;
    p->next=*s;
    *s=p;
    return 1;
}

//��ջ��ջ
int Pop(LinkStack *s,int *e)
{
    StackNode *p=(StackNode *)malloc(sizeof(StackNode));
    if(*s==NULL){
        return 0;
    }
    *e=(*s)->data;
    p=*s;
    *s=(*s)->next;
    free(p);
    return 1;

}

//ȡ��ջջ��Ԫ��
int GetTop(LinkStack *s)
{
    if(*s!=NULL){
        return (*s)->data;
    }
}

int main()
{   

    //��ջ
    StackNode *s=(StackNode *)malloc(sizeof(StackNode));
    int a=3;
    int b=2;
    int c=1;
    int d=5;
    int e;
    InitStack(&s);
    Push(&s,a);
    Push(&s,b);
    Push(&s,c);
    Pop(&s,&e);
    Pop(&s,&e);
    Push(&s,d);
    Pop(&s,&e);
    printf("%d",e);


    //˳��ջ
    // SqStack *s=(SqStack *)malloc(sizeof(SqStack));
    // int a=3;
    // int b=2;
    // int c=1;
    // int e;
    // InitStack(s);
    // Push(s,a);
    // Push(s,b);
    // Push(s,c);
    // Pop(s,&e);
    // printf("%d",GetTop(*s));
    return 0;
}