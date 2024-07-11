#include<stdio.h>
#include<stdlib.h>
#define MaxInt 32767
#define MVNum 100
#define true 1  //表示确定
#define false 0  //表示尚未确定

typedef char VerTexType;
typedef int ArcType;

typedef struct
{
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum,arcnum;
}AMGraph;

void ShortestPath_DIJ(AMGraph G,int v0)
{
    int n = G.vexnum;
    int v;
    int S[n];
    int Path[n];
    int D[n];
    for(v = 0;v < n;v++)
    {
        S[v] = false;
        D[v] = G.arcs[v0][v];
        if(D[v] < MaxInt)
            Path[v] = v0;
        else    
            Path[v] = -1;
    }
    S[v0] = true;
    D[v0] = 0;
/*------------初始化结束，开始主循环----------------*/
    for(int i = 1;i < n;i++)
    {
        int min = MaxInt;
        for(int w = 0;w < n;w++)
            if(!S[w] && D[w] < min)
            {
                v = w;
                min = D[w];
            }
        S[v] = true;
        for(int w = 0;w < n;w++)
        if(!S[w] && D[v] + G.arcs[v][w] < D[w])
        {
            D[w] = D[v] + G.arcs[v][w];
            Path[w] = v;
        }
    }
}