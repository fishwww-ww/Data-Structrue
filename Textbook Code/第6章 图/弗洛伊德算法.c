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
    int vexnum, arcnum;
}AMGraph;

void Shortest_Floyd(AMGraph G)
{
    int Path[G.vexnum][G.vexnum];
    int D[G.vexnum][G.vexnum];
    for(int i = 0;i < G.vexnum;i++)
        for(int j = 0;j < G.vexnum;j++)
        {
            D[i][j] = G.arcs[i][j];
            if(D[i][j] < MaxInt && i != j)
                Path[i][j] = i;
            else    
                Path[i][j] = -1;
        }
    for(int k = 0;k < G.vexnum;k++)
        for(int j = 0;j < G.vexnum;j++)
            for(int i = 0;i < G.vexnum;i++)
                if(D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    Path[i][j] = Path[k][j];
                }

}