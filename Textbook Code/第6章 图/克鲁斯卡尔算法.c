#include<stdio.h>
#include<stdlib.h>
#define MaxInt 32767
#define MVNum 100
typedef char VerTexType;
typedef int ArcType;

typedef struct
{
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum,arcnum;
}AMGraph;


typedef struct
{
    VerTexType Head;
    VerTexType Tail;
    ArcType lowcost;
}EDGE;

int LocateVex(AMGraph G,VerTexType u)
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(u==G.vexs[i])
        {
            return i;
        }
    }
    return -1;
}

int cmp(const void *a,const void *b)
{
    return ((EDGE *)a)->lowcost-((EDGE *)b)->lowcost;
}


void MiniSpanTree_Kruskal(AMGraph G)
{
    EDGE Edge[G.arcnum];

    int Vexset[MVNum];
    int v1,v2,vs1,vs2;

    qsort(Edge,G.arcnum,sizeof(Edge[0])*G.arcnum,cmp);
    
    for(int i=0;i<G.vexnum;i++)
        Vexset[i]=i;
    for(int i=0;i<G.arcnum;i++)
    {
        v1=LocateVex(G,Edge[i].Head);
        v2=LocateVex(G,Edge[i].Tail);
        vs1=Vexset[v1];
        vs2=Vexset[v2];
        if(vs1!=vs2)
        {
            printf("%c %c\n",Edge[i].Head,Edge[i].Tail);
            for(int j=0;j<G.vexnum;j++)
                if(Vexset[j]==vs2)
                    Vexset[j]=vs1;
        }
    }
}