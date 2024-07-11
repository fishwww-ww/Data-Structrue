#include<stdio.h>
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

int CreateUDN(AMGraph *G)
{
    int i,j,k,w;
    VerTexType v1,v2;
    scanf("%d %d",&(G->vexnum),&(G->arcnum));
    for(i=0;i<G->vexnum;i++)
    {
        scanf("%d",&(G->vexs[i]));
    }
    for(i=0;i<G->vexnum;i++)
    {
        for(j=0;j<G->vexnum;j++)
        {
            G->arcs[i][j]=MaxInt;
        }
    }
    for(k=0;k<G->arcnum;k++)
    {
        scanf("%c%c%d",&v1,&v2,&w);
        i=Locatevex(G,v1);
        j=Locatevex(G,v2);
        G->arcs[i][j]=w;
        G->arcs[j][i]=G->arcs[i][j];
    }
    return 1;
}