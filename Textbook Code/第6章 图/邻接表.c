#include<stdio.h>
#include<stdlib.h>
#define MaxInt 32767
#define MVNum 100
#define OtherInfo int
typedef char VerTexType;
typedef int ArcType;

//图的邻接表存储表示
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    OtherInfo info;
}ArcNode;
typedef struct VNode
{
    VerTexType data;
    ArcNode *firstarc;
}VNode,AdjList[MVNum];
typedef struct 
{
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;


int LocateVex(ALGraph G,VerTexType u)
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(u==G.vertices[i].data)
        {
            return i;
        }
    }
    return -1;
}

//采用邻接链表表示法创建无向图
void CreateUDG(ALGraph *G)
{
    scanf("%d%d",G->vexnum,G->arcnum);
    for(int i=0;i<G->vexnum;i++)
    {
        scanf("%c",&G->vertices[i].data);
        G->vertices[i].firstarc=NULL;
    }
    VerTexType v1,v2;
    for(int k=0;k<G->arcnum;k++)
    {
        scanf("%c%c",&v1,&v2);
        int i=LocateVex(*G,v1);
        int j=LocateVex(*G,v2);
        ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));
        p1->adjvex=j;
        p1->nextarc=G->vertices[i].firstarc;
        G->vertices[i].firstarc=p1;
        ArcNode *p2=(ArcNode *)malloc(sizeof(ArcNode));
        p2->adjvex=i;
        p2->nextarc=G->vertices[j].firstarc;
        G->vertices[j].firstarc=p2;
    }
}