#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//ͼ���ڽӾ���洢��ʾ
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


//ͼ���ڽӱ�洢��ʾ
#define MVNum 100
#define OtherInfo int
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


//�����������������ͨͼ
bool visited[MVNum];

// void DFS(Graph G,int v)
// {
//     //
//     visited[v]=true;
//     for(int w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
//     {
//         if(!visited[w])
//         {
//             DFS(G,w);
//         }
//     }
// }

// //�������������������ͨͼ
// void DFSTraverse(Graph G)
// {
//     int v;
//     for(v=0;v<)
// }

int Locatevex(AMGraph G, int v);
{

}

//�����ڽӾ����ʾͼ�����������������
void DFS_AM(AMGraph G,int v)//�ӵ�v���������
{
    printf("%d", v);
    visited[v]=true;
    for(int w=0;w<G.vexnum;w++)
    {
        if(G.arcs[v][w]!=0 && !visited[w])
        {
            DFS_AM(G,w);
        }
    }
}

//�����ڽӱ��ʾͼ�����������������
void DFS_AL(ALGraph G,int v)
{
    printf("%d", v);
    visited[v]=true;
    ArcNode *p = G.vertices[v].firstarc;
    int w;
    while (p!=NULL)
    {
        w=p->adjvex;
        if(!visited[w])
        {
            DFS_AL(G,w);
        }
        p=p->nextarc;
    }
}

//�����ڽӾ����ʾ������������
void CreateUDN(AMGraph *G)
{
    int i,j,k,w;
    VerTexType v1,v2;
    scanf("%d %d",&(G->vexnum),&(G->arcnum));
    for(i=0;i<G->vexnum;i++)
    {
        scanf("%c",&(G->vexs[i]));//��������Ϣ
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
    printf("Finish creating\n");
}

int main()
{
    AMGraph *G;
    CreateUDN(G);
    DFS_AM(*G,1);
}