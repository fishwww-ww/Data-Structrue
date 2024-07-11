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
    VerTexType adjvex;
    ArcType lowcost;
}Closedge;

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

int Min(Closedge *closedge,AMGraph G)
{
    int mincost=0;
    for(int i=0;i<G.vexnum;i++)
    {
        if(closedge[i].lowcost<closedge[i+1].lowcost)
            mincost=i;
    }
    return mincost;
}

void MiniSpanTree_Prim(AMGraph G,VerTexType u)
{
    Closedge closedge[MVNum];
    int k=LocateVex(G,u);
    for(int j=0;j<G.vexnum;j++)
        if(j!=k)
        {
            closedge[j].adjvex=u;
            closedge[j].lowcost=G.arcs[k][j];
        }
    closedge[k].lowcost=0;
    for(int i=1;i<G.vexnum;i++)
    {
        k=Min(closedge,G);
        VerTexType u0=closedge[k].adjvex;
        VerTexType v0=G.vexs[k];
        printf("%c %c\n",u0,v0);
        closedge[k].lowcost=0;
        for(int j=0;j<G.vexnum;j++)
            if(G.arcs[k][j]<closedge[j].lowcost)
            {
                closedge[j].adjvex=G.vexs[k];
                closedge[j].lowcost=G.arcs[k][j];
            }
    }
}