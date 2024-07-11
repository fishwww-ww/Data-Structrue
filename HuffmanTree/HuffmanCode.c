#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 100

//���������Ĵ洢��ʾ
typedef struct 
{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;

//�����������Ĵ洢��ʾ
typedef char **HuffmanCode;

//�ַ����ͳ���Ƶ��
typedef struct
{
    char ch;
    int numOfLetter;
}Letter;

//�ĸ���������
void Select(HuffmanTree HT,int n,int *s1,int *s2);
void CreateHuffmanTree(HuffmanTree *HT,int n,Letter *letter);
void CreateHuffmanCode(HuffmanTree HT,HuffmanCode *HC,int n);
void Statistic(char *input,int *n,int *frequency);
int Conserve(Letter *letter,char ch,int n);

//������
int main()
{
    char input[MAXLEN][MAXLEN];          
    for(int i=0;i<=MAXLEN;i++)
    {
        //1.���벢����������
        scanf("%s",input[i]);        
        if(input[i][0]=='0')                           //�˳�ѭ������
            break;  
        int n=0;                                       //�ַ�������
        int length=strlen(input[i]);                   //ÿ���ַ������ַ�����
        int frequency[26]={0};                         //ÿ���ַ�����Ƶ��
        Statistic(input[i],&n,frequency);              //ͳ���ַ��������ͳ���Ƶ��
        Letter letter[n+1];                            //���ڵ��ַ�����Ƶ��
        for(int i=0,j=1;i<26;i++)  
        {
            if(frequency[i]!=0)                        //�����ڵ��ַ�ͳ�ƺò�����letter
            {
                letter[j].ch='a'+i;                 
                letter[j].numOfLetter=frequency[i];    
                j++;
            }
        }

        //2.�������������������
        HuffmanTree HT;        
        CreateHuffmanTree(&HT,n,letter);               //������������
        HuffmanCode HC;
        CreateHuffmanCode(HT,&HC,n);                   //��������������

        //3.������
        for(int i=1;i<=n;i++)
        {
            //������ڵ��ַ��������Ƶ��
            printf("%c:%d ",letter[i].ch,letter[i].numOfLetter);
            if(i==n)
                printf("\n");
        }
        for(int i=1;i<=2*n-1;i++)
        {
            //���HT����̬
            printf("%d %d %d %d %d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
        }
        for(int i=1;i<=n;i++)
        {
            //���ÿ���ַ��Ĺ���������
            printf("%c:%s ",letter[i].ch,HC[i]);
            if(i==n)
                printf("\n");
        }
        for(int j=0;j<length;j++)
        {
            //����������ַ���
            printf("%s",HC[Conserve(letter,input[i][j],n)]);
            if(j==length-1)
                printf("\n");
        }
        //����������ַ���
        printf("%s\n",input[i]);
    }
}

//��i-1�������ѡ��˫����Ϊ0��Ȩֵ��С���������
void Select(HuffmanTree HT,int n,int *s1,int *s2)
{
    int min=1000;                                         //��ֵ����ʵ�����ȡ�ϴ�ֵ����
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(HT[i].parent==0 && HT[j].parent==0 && i!=j)
                if(HT[i].weight+HT[j].weight<min)
                {
                    min=HT[i].weight+HT[j].weight;
                    *s1=i;
                    *s2=j;
                    if(HT[*s1].weight > HT[*s2].weight)  //��ֹs1������Ľ���Ȩֵ>s2��
                        *s1^=*s2^=*s1^=*s2;              //������ֵ
                }
}

//�����������
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
            (*HT)[i].weight=letter[i].numOfLetter;     //��ͳ�ƺõ��ַ�Ƶ�ʸ�ֵ��HT��Ȩֵ
    }
/*---------��ʼ����������ʼ������������-----------*/
    int s1,s2;
    for(int i=n+1;i<=m;i++)
    {
        Select(*HT,i-1,&s1,&s2);                       //�涨s1������Ľ���Ȩֵ<=s2��
        (*HT)[s1].parent=i;
        (*HT)[s2].parent=i;
        (*HT)[i].lchild=s1;
        (*HT)[i].rchild=s2;
        (*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
    }
}

//�������������
void CreateHuffmanCode(HuffmanTree HT,HuffmanCode *HC,int n)
{
    *HC=(char **)malloc((n+1) * sizeof(char *));             //����n+1��char*�Ŀռ�
    char *cd=(char *)malloc(n * sizeof(char));               //����n��char�Ŀռ�
    cd[n-1]='\0';                                            //��cd��β��ӽ�����
    for(int i=1;i<=n;i++)
    {
        int start=n-1;                                       //��ΪҪ�����cd��ֵ������start��ֵΪn-1
        int c=i;
        int f=HT[i].parent;                                  //f������c��˫�׽������
        while (f!=0)
        {
            start--;
            if(HT[f].lchild == c)                            //����
                cd[start]='0';
            else                                             //�ҽ��
                cd[start]='1';
            c=f;
            f=HT[f].parent;
        }
        (*HC)[i]=(char *)malloc((n-start) * sizeof(char));   //����������Ҫ�Ŀռ䣬���˷Ѵ洢
        strcpy((*HC)[i],cd+start);                           //����õı��븳ֵ��*HC��ǰ��                          
    }
    free(cd);                                                //�ͷſռ�
}

//ͳ���ַ��������ͳ���Ƶ��
void Statistic(char *input,int *n,int *frequency)
{
    (*n)=0;
    int ascii;
    for(int i=0;input[i]!='\0';i++)
    {
        ascii=input[i]-'a';                                  //��ǰ�ַ���'a'�ľ���
        frequency[ascii]++;                                  //��ǰ�ַ�����Ƶ��++
    }
    for(int i=0;i<26;i++)
        if(frequency[i]!=0)
            (*n)++;                                          //���ֵ��ַ�����++
}

//����ʱ������ַ�ת��Ϊ���ַ���letter�����е��±�
int Conserve(Letter *letter,char ch,int n)
{
    for(int i=1;i<=n;i++)
        if((letter+i)->ch == ch)
            return i;
}