#include <stdio.h>
#include <stdlib.h>
#define maxqsize 100

// //ѭ�����У�˳����У�����
// typedef struct 
// {
//     int *base;
//     int front;
//     int rear;
// }SqQueue;

// //ѭ�����г�ʼ��
// int InitQueue(SqQueue *q)
// {
//     q->base=(int *)malloc(sizeof(int));
//     if(!q->base){
//         exit(0);
//     }
//     q->front=q->rear=0;
//     return 1;
// }

// //��ѭ�����г���
// int QueueLength(SqQueue q)
// {
//     return (q.rear-q.front+maxqsize)%maxqsize;
// }

// //ѭ���������
// int EnQueue(SqQueue *q,int e)
// {
//     if((q->rear+1)%maxqsize==q->front){
//         return 0;
//     }
//     q->base[q->rear]=e;
//     q->rear=(q->rear+1)%maxqsize;
//     return 1;
// }

// //ѭ�����г���
// int DeQueue(SqQueue *q,int *e)
// {
//     if(q->front==q->rear){
//         return 0;
//     }
//     *e=q->base[q->front];
//     q->front=(q->front+1)%maxqsize;
//     return 1;
// }

// //ȡѭ�����ж�ͷԪ��
// int GetHead(SqQueue q)
// {
//     if(q.front!=q.rear){
//         return q.base[q.front];
//     }
// }




//������
typedef struct QNode
{
    int data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

//���ӳ�ʼ��
int InitQueue(LinkQueue *q)
{
    q->front=(QueuePtr)malloc(sizeof(QNode));
    q->rear=(QueuePtr)malloc(sizeof(QNode));
    q->front->next=NULL;
    return 1;
}

//���������
int EnQueue(LinkQueue *q,int e)
{
    QNode *p=(QNode *)malloc(sizeof(QNode));
    p->data=e;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
    return 1;
}

//�����г���
int DeQueue(LinkQueue *q,int *e)
{
    QNode *p=(QNode *)malloc(sizeof(QNode));
    if(q->front==q->rear){
        return 0;
    }
    p=q->front->next;
    *e=p->data;
    q->front->next=p->next;
    if(q->rear==p){
        q->rear=q->front;
    }
    free(p);
    return 1;
}

//ȡ���ӵĶ�ͷԪ��
int GetHead(LinkQueue q)
{
    if(q.front!=q.rear){
        return q.front->next->data;
    }
}


int main()
{
    //������
    LinkQueue *q=(LinkQueue *)malloc(sizeof(LinkQueue));
    int a=3;
    int b=2;
    int c=1;
    int e=7;
    InitQueue(q);
    EnQueue(q,a);
    EnQueue(q,b);
    EnQueue(q,c);
    DeQueue(q,&e);
    printf("e:%d\n",e);
    printf("head:%d\n",GetHead(*q));



    // //ѭ������
    // SqQueue *q=(SqQueue *)malloc(sizeof(SqQueue));
    // int a=3;
    // int b=2;
    // int c=1;
    // int e=7;
    // InitQueue(q);
    // EnQueue(q,a);
    // EnQueue(q,b);
    // EnQueue(q,c);
    // DeQueue(q,&e);
    // printf("head:%d\n",GetHead(*q));
    // printf("e:%d\n",e);
    // printf("length:%d\n",QueueLength(*q));
    return 0;
}