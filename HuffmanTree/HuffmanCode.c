#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 100

//哈夫曼树的存储表示
typedef struct 
{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;

//哈夫曼编码表的存储表示
typedef char **HuffmanCode;

//字符类别和出现频率
typedef struct
{
    char ch;
    int numOfLetter;
}Letter;

//四个函数声明
void Select(HuffmanTree HT,int n,int *s1,int *s2);
void CreateHuffmanTree(HuffmanTree *HT,int n,Letter *letter);
void CreateHuffmanCode(HuffmanTree HT,HuffmanCode *HC,int n);
void Statistic(char *input,int *n,int *frequency);
int Conserve(Letter *letter,char ch,int n);

//主函数
int main()
{
    char input[MAXLEN][MAXLEN];          
    for(int i=0;i<=MAXLEN;i++)
    {
        //1.输入并处理输入结果
        scanf("%s",input[i]);        
        if(input[i][0]=='0')                           //退出循环条件
            break;  
        int n=0;                                       //字符类别个数
        int length=strlen(input[i]);                   //每行字符串的字符个数
        int frequency[26]={0};                         //每个字符出现频率
        Statistic(input[i],&n,frequency);              //统计字符类别个数和出现频率
        Letter letter[n+1];                            //存在的字符及其频率
        for(int i=0,j=1;i<26;i++)  
        {
            if(frequency[i]!=0)                        //将存在的字符统计好并赋给letter
            {
                letter[j].ch='a'+i;                 
                letter[j].numOfLetter=frequency[i];    
                j++;
            }
        }

        //2.构建哈夫曼树及其编码
        HuffmanTree HT;        
        CreateHuffmanTree(&HT,n,letter);               //创建哈夫曼树
        HuffmanCode HC;
        CreateHuffmanCode(HT,&HC,n);                   //构建哈夫曼编码

        //3.输出结果
        for(int i=1;i<=n;i++)
        {
            //输出存在的字符及其出现频率
            printf("%c:%d ",letter[i].ch,letter[i].numOfLetter);
            if(i==n)
                printf("\n");
        }
        for(int i=1;i<=2*n-1;i++)
        {
            //输出HT表终态
            printf("%d %d %d %d %d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
        }
        for(int i=1;i<=n;i++)
        {
            //输出每个字符的哈夫曼编码
            printf("%c:%s ",letter[i].ch,HC[i]);
            if(i==n)
                printf("\n");
        }
        for(int j=0;j<length;j++)
        {
            //输出编码后的字符串
            printf("%s",HC[Conserve(letter,input[i][j],n)]);
            if(j==length-1)
                printf("\n");
        }
        //输出解码后的字符串
        printf("%s\n",input[i]);
    }
}

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
void CreateHuffmanTree(HuffmanTree *HT,int n,Letter *letter)
{
    if(n<=1)
        exit(0);
    int m=2*n-1;
    *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
    for(int i=1;i<=m;i++)
    {
        (*HT)[i].parent=0;
        (*HT)[i].lchild=0;
        (*HT)[i].rchild=0;
        if(i<n+1)
            (*HT)[i].weight=letter[i].numOfLetter;     //将统计好的字符频率赋值给HT的权值
    }
/*---------初始化结束，开始创建哈夫曼树-----------*/
    int s1,s2;
    for(int i=n+1;i<=m;i++)
    {
        Select(*HT,i-1,&s1,&s2);                       //规定s1所代表的结点的权值<=s2的
        (*HT)[s1].parent=i;
        (*HT)[s2].parent=i;
        (*HT)[i].lchild=s1;
        (*HT)[i].rchild=s2;
        (*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
    }
}

//构造哈夫曼编码
void CreateHuffmanCode(HuffmanTree HT,HuffmanCode *HC,int n)
{
    *HC=(char **)malloc((n+1) * sizeof(char *));             //分配n+1个char*的空间
    char *cd=(char *)malloc(n * sizeof(char));               //分配n个char的空间
    cd[n-1]='\0';                                            //在cd结尾添加结束符
    for(int i=1;i<=n;i++)
    {
        int start=n-1;                                       //因为要倒序给cd赋值，所以start初值为n-1
        int c=i;
        int f=HT[i].parent;                                  //f代表结点c的双亲结点的序号
        while (f!=0)
        {
            start--;
            if(HT[f].lchild == c)                            //左结点
                cd[start]='0';
            else                                             //右结点
                cd[start]='1';
            c=f;
            f=HT[f].parent;
        }
        (*HC)[i]=(char *)malloc((n-start) * sizeof(char));   //仅分配所需要的空间，不浪费存储
        strcpy((*HC)[i],cd+start);                           //将求得的编码赋值到*HC当前行                          
    }
    free(cd);                                                //释放空间
}

//统计字符类别个数和出现频率
void Statistic(char *input,int *n,int *frequency)
{
    (*n)=0;
    int ascii;
    for(int i=0;input[i]!='\0';i++)
    {
        ascii=input[i]-'a';                                  //当前字符与'a'的距离
        frequency[ascii]++;                                  //当前字符出现频率++
    }
    for(int i=0;i<26;i++)
        if(frequency[i]!=0)
            (*n)++;                                          //出现的字符种类++
}

//将此时处理的字符转化为该字符在letter数组中的下标
int Conserve(Letter *letter,char ch,int n)
{
    for(int i=1;i<=n;i++)
        if((letter+i)->ch == ch)
            return i;
}