#include<stdio.h>
#include<stdbool.h>
#define MaxInt 32767   //��ʾ���������������Զ
#define MVNum 100

//ͼ���ڽӾ���洢��ʾ
typedef struct
{
    char vexs[MVNum];
    int arcs[MVNum][MVNum];
    int vexnum, arcnum;
}AMGraph;

//�Ͻ�˹�����㷨
void ShortestPath_DIJ (AMGraph G, char start, char end)
{
    int v0 = start - 'A' + 0;
    int n = G.vexnum;                                            //ͼ�Ķ������
    int v;
    bool S[n];                                                   //Դ�㵽�յ��Ƿ�ȷ�����·������
    int Path[n];                                                 //���·��ֱ��ǰ����������
    int D[n];                                                    //Դ�㵽�յ�����·������
    for (v = 0;v < n;v++)
    {
        S[v] = false;                                            //��ʼΪ�ռ�
        D[v] = G.arcs[v0][v];                                    //��ʼ��Ϊ����Ȩֵ
        if (D[v] < MaxInt)                                       //������л�
            Path[v] = v0;
        else                                                     //������޻�
            Path[v] = -1;
    }
    S[v0] = true;
    D[v0] = 0;                                                   //Դ�㵽Դ�����Ϊ0
/*------------��ʼ����������ʼ��ѭ��---------------*/
    for (int i = 1;i < n;i++)
    {
        int min = MaxInt;
        for (int w = 0;w < n;w++)
            if (!S[w] && D[w] < min)                             //����ǰ�����·��
            {
                v = w;                                           //�����м��       
                min = D[w];                                      //�������·��
            }
        S[v] = true;                                             //�м�õ������·��
        for (int w = 0;w < n;w++)                                //����Դ�㵽ĳ�ص����·��
            if (!S[w] && D[v] + G.arcs[v][w] < D[w])
            {
                D[w] = D[v] + G.arcs[v][w];//�������·��
                Path[w] = v;//����ֱ��ǰ��
            }
    }
/*--------------���·��Ѱ����ϣ���ʼ���--------------------*/
    int endToStart = end - 'A' + 0;                              //���յ㿪ʼ���ݵ����
    int city = 1;                                                //���·�������ĳ�����
    char pathCity[MVNum];                                        //���·�������ĳ���
    pathCity[0] = G.vexs[endToStart];                            //�յ����
    printf ("%d\n", D[endToStart]);                              //������·��ֵ
    for (int i = 1;i < MVNum;i++)
    {
        if (endToStart == v0)                                    //���������㣬���˳�ѭ��
            break;
        city++;
        endToStart = Path[endToStart];                           //���յ㿪ʼ��ǰ����
        pathCity[i] = G.vexs[endToStart];
    }
    for (int i = city - 1;i >= 0;i--)                            //�������
    {
        printf("%c", pathCity[i]);
        if(i > 0)
            printf(" ");
        else
            printf("\n");
    }
}

//����������
int main ()
{
    AMGraph G;
    char ch1, ch2;                                               //�����ַ�������ѭ���н��ݴ�ĳЩֵ
    char start, end;                                             //�����к��յ����
    while (1)
    {
        scanf ("%d%d", &G.vexnum, &G.arcnum);                    //��������·����
        getchar();
        if (G.vexnum == 0 && G.arcnum == 0)                      //��Ϊ0���˳�ѭ��
            break;
        for (int i = 0;i < G.vexnum;i++)
        {
            scanf ("%c", &G.vexs[i]);                            //ÿ�����е�����
            getchar();
        }
        for (int i = 0;i < G.vexnum;i++)
            for (int j = 0;j < G.vexnum;j++)
                G.arcs[i][j] = MaxInt;                           //�Ƚ�����·����ʼ��Ϊ���ֵ
        for (int i = 0;i < G.arcnum;i++)
        {
            scanf ("%c", &ch1);                                  //����1
            getchar();
            scanf ("%c", &ch2);                                  //����2
            getchar();
            scanf("%d", &G.arcs[ch1 - 'A' + 0][ch2 - 'A' + 0]);  //����1��2���·����Ȩֵ
            getchar();
        }
        scanf ("%c %c", &start, &end);                           //�����յ�
/*---------------------�����������ʼ������·��-----------------------------*/
        ShortestPath_DIJ (G, start, end);
    }
    return 0;
}