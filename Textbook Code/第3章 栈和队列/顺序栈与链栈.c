#include <stdio.h>
#include <stdlib.h>
#define maxsize 100

// //À≥–Ú’ª
// typedef struct 
// {
//     int *base;
//     int *top;
//     int stacksize;
// }SqStack;

// //À≥–Ú’ª≥ı ºªØ
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

// //À≥–Ú’ª»Î’ª
// int Push(SqStack *s,int e)
// {
//     if(s->top-s->base==s->stacksize){
//         return 0;
//     }
//     *(s->top)=e;
//     s->top++;
//     return 1;
// }

// //À≥–Ú’ª≥ˆ’ª
// int Pop(SqStack *s,int *e)
// {
//     if(s->top==s->base){
//         return 0;
//     }
//     s->top--;
//     *e=*(s->top);
//     return 1;
// }

// //»°À≥–Ú’ª’ª∂•‘™Àÿ
// int GetTop(SqStack s)
// {
//     if(s.top!=s.base){
//         return *(s.top-1);
//     }
// }



//¡¥’ª
typedef struct StackNode
{
    int data;
    struct StackNode *next;
}StackNode,*LinkStack;

//¡¥’ª≥ı ºªØ
int InitStack(LinkStack *s)
{
    *s=NULL;  //*s=NULL;
    return 1;
}

//¡¥’ª»Î’ª
int Push(LinkStack *s,int e)
{
    StackNode *p=(StackNode *)malloc(sizeof(StackNode));
    p->data=e;
    p->next=*s;
    *s=p;
    return 1;
}

//¡¥’ª≥ˆ’ª
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

//»°¡¥’ª’ª∂•‘™Àÿ
int GetTop(LinkStack *s)
{
    if(*s!=NULL){
        return (*s)->data;
    }
}

int main()
{   

    //¡¥’ª
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


    //À≥–Ú’ª
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