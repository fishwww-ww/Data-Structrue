#include<stdio.h>
#include<stdbool.h>
#define MaxInt 32767   //表示两个顶点相距无穷远
#define MVNum 100

//图的邻接矩阵存储表示
typedef struct
{
    char vexs[MVNum];
    int arcs[MVNum][MVNum];
    int vexnum, arcnum;
}AMGraph;

//迪杰斯特拉算法
void ShortestPath_DIJ (AMGraph G, char start, char end)
{
    int v0 = start - 'A' + 0;
    int n = G.vexnum;                                            //图的顶点个数
    int v;
    bool S[n];                                                   //源点到终点是否确定最短路径长度
    int Path[n];                                                 //最短路径直接前驱顶点的序号
    int D[n];                                                    //源点到终点的最短路径长度
    for (v = 0;v < n;v++)
    {
        S[v] = false;                                            //初始为空集
        D[v] = G.arcs[v0][v];                                    //初始化为弧的权值
        if (D[v] < MaxInt)                                       //两点间有弧
            Path[v] = v0;
        else                                                     //两点间无弧
            Path[v] = -1;
    }
    S[v0] = true;
    D[v0] = 0;                                                   //源点到源点距离为0
/*------------初始化结束，开始主循环---------------*/
    for (int i = 1;i < n;i++)
    {
        int min = MaxInt;
        for (int w = 0;w < n;w++)
            if (!S[w] && D[w] < min)                             //若当前有最短路径
            {
                v = w;                                           //更新中间点       
                min = D[w];                                      //更新最短路径
            }
        S[v] = true;                                             //中间该店有最短路径
        for (int w = 0;w < n;w++)                                //更新源点到某地的最短路径
            if (!S[w] && D[v] + G.arcs[v][w] < D[w])
            {
                D[w] = D[v] + G.arcs[v][w];//更新最短路径
                Path[w] = v;//更改直接前驱
            }
    }
/*--------------最短路径寻找完毕，开始输出--------------------*/
    int endToStart = end - 'A' + 0;                              //从终点开始回溯到起点
    int city = 1;                                                //最短路径经过的城市数
    char pathCity[MVNum];                                        //最短路径经过的城市
    pathCity[0] = G.vexs[endToStart];                            //终点城市
    printf ("%d\n", D[endToStart]);                              //输出最短路径值
    for (int i = 1;i < MVNum;i++)
    {
        if (endToStart == v0)                                    //如果到达起点，则退出循环
            break;
        city++;
        endToStart = Path[endToStart];                           //从终点开始往前回溯
        pathCity[i] = G.vexs[endToStart];
    }
    for (int i = city - 1;i >= 0;i--)                            //倒序输出
    {
        printf("%c", pathCity[i]);
        if(i > 0)
            printf(" ");
        else
            printf("\n");
    }
}

//程序主函数
int main ()
{
    AMGraph G;
    char ch1, ch2;                                               //两个字符变量在循环中将暂存某些值
    char start, end;                                             //起点城市和终点城市
    while (1)
    {
        scanf ("%d%d", &G.vexnum, &G.arcnum);                    //城市数和路径数
        getchar();
        if (G.vexnum == 0 && G.arcnum == 0)                      //都为0则退出循环
            break;
        for (int i = 0;i < G.vexnum;i++)
        {
            scanf ("%c", &G.vexs[i]);                            //每个城市的名称
            getchar();
        }
        for (int i = 0;i < G.vexnum;i++)
            for (int j = 0;j < G.vexnum;j++)
                G.arcs[i][j] = MaxInt;                           //先将所以路径初始化为最大值
        for (int i = 0;i < G.arcnum;i++)
        {
            scanf ("%c", &ch1);                                  //城市1
            getchar();
            scanf ("%c", &ch2);                                  //城市2
            getchar();
            scanf("%d", &G.arcs[ch1 - 'A' + 0][ch2 - 'A' + 0]);  //城市1、2间的路径的权值
            getchar();
        }
        scanf ("%c %c", &start, &end);                           //起点和终点
/*---------------------输入结束，开始求解最短路径-----------------------------*/
        ShortestPath_DIJ (G, start, end);
    }
    return 0;
}