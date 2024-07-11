#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXLEN 100

//哈夫曼树的存储表示
typedef struct 
{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;

//哈夫曼编码表的存储表示
typedef char **HuffmanCode;

//在i-1个结点中选择双亲域为0且权值最小的两个结点
void Select(HuffmanTree HT,int n,int *s1,int *s2)
{
    int min=1000;                                         //初值根据实际情况取较大值即可
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(HT[i].parent==0 && HT[j].parent==0 && i!=j)
                if(HT[i].weight+HT[j].weight<min)
                {
                    min=HT[i].weight+HT[j].weight;
                    *s1=i;
                    *s2=j;
                    if(HT[*s1].weight > HT[*s2].weight)  //防止s1所代表的结点的权值>s2的
                        *s1^=*s2^=*s1^=*s2;              //交换数值
                }
}

//构造哈夫曼树
void CreateHuffmanTree(HuffmanTree *HT,int n)
{
    if(n<=1)
        exit(0);
    int m=2*n-1;
    *HT=(HuffmanTree)malloc(sizeof(HTNode)*2*n);
    for(int i=1;i<m+1;i++)
    {
        (*HT+i)->parent=0;
        (*HT+i)->lchild=0;
        (*HT+i)->rchild=0;
        if(i<n+1)
            scanf("%d",&(*HT+i)->weight);                      //将统计好的字符频率赋值给HT的权值
    }
/*---------初始化结束，开始创建哈夫曼树-----------*/
    int s1,s2;
    for(int i=n+1;i<m+1;i++)
    {
        Select(*HT,i-1,&s1,&s2);           //规定s1<=s2
        (*HT+s1)->parent=i;
        (*HT+s2)->parent=i;
        (*HT+i)->lchild=s1;
        (*HT+i)->rchild=s2;
        (*HT+i)->weight=(*HT+s1)->weight+(*HT+s2)->weight;
    }
}

//哈夫曼编码
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n) {
    *HC=(char **)malloc((n + 1)*sizeof(char *));
    char *cd = (char *)malloc(n*sizeof(char));
    cd[n-1]='\0';
    for (int i=1;i<=n;i++)
    {
        int start=n-1;
        int c=i;
        int f=HT[c].parent; // f代表结点c的双亲结点的序号
        while (f!= 0) 
        {
            start--;
            if(HT[f].lchild == c) 
                cd[start]='0';
            else 
                cd[start]='1';
            c=f;
            f=HT[c].parent;
        }
        (*HC)[i]=(char *)malloc((n-start)*sizeof(char));
        strcpy((*HC)[i],cd+start);
    }
    free(cd);
}

int main()
{
    int n=3;
    HuffmanTree HT;
    HuffmanCode HC;
    CreateHuffmanTree(&HT,n);
    CreateHuffmanCode(HT,&HC,n);
    for(int i=1;i<=n;i++)
    {
        printf("%d %d %d %d %d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
        printf("%s\n",HC[i]);
    }
}