#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 255

//���Ķ���˳��洢
typedef struct
{
    char ch[MAXLEN+1];
    int length;
}SString;

//BF�㷨
int Index_BF(SString S,SString T,int pos)
{
    int i=pos;
    int j=0;                                                       //�α������1��ʼ��Ϊ�±�������������0��ʼ
    while(i<S.length && j<T.length)
    {
        if(S.ch[i]==T.ch[j]){
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(j>=T.length)
    {
        return i-T.length+1;
    }
    else
    {
        return 0;
    }
}

//����BF�㷨ʵ�ֲ������
int main()
{
    SString Virus;                                                 //������DNA����
    SString Person;                                                //�˵�DNA����
    SString temp;                                                  //�ݴ没��DNAÿ�εĻ�״����
    char Vir[MAXLEN];                                              //�ݴ没���ĳ�ʼDNA����
    int flag=0;                                                    //������ʶ�Ƿ�ƥ�䣬��ʼΪ0��ƥ���Ϊ��0
    int m;                                                         //����DNA���еĳ���
    int num;                                                       //������������
    FILE *inFile=fopen("D:\\������Ⱦ�����������1.txt","a+");        //���������
    FILE *outFile=fopen("D:\\������Ⱦ���������.txt","w+");        //���������
    rewind(inFile);
    fscanf(inFile,"%d",&num);
    while (num--)
    {
        fscanf(inFile,"%s",Virus.ch);                              //��ȡ����������
        fscanf(inFile,"%s",Person.ch);                             //��ȡ�˵�����      
        Virus.length=strlen(Virus.ch);                     
        Person.length=strlen(Person.ch);                     
        temp.length=strlen(Virus.ch);                     
        strcpy(Vir,Virus.ch);
        flag=0;
        m=Virus.length;
        for(int i=m,j=0;j<m;j++)
        {
            Virus.ch[i]=Virus.ch[j];                               //�������ַ���������������
            i++;
        }
        Virus.ch[2*m]='\0';                                        //��ӽ�����
        for(int i=0;i<m;i++)                                       //ȡÿ������Ϊm�Ĳ���DNA��״��temp
        {
            for(int j=0;j<m;j++)
            {
                temp.ch[j]=Virus.ch[i+j];
            }
            temp.ch[m]='\0';                                       //��ӽ�����
            flag=Index_BF(Person,temp,0);                          //BF�㷨ģʽƥ��
            if(flag)
            {
                break;
            }
        }
        if(flag)
        {
            fprintf(outFile,"%-10s","YES");
            fprintf(outFile,"%-10s",Vir);
            fprintf(outFile,"%-10s\n",Person.ch);
        }
        else
        {
            fprintf(outFile,"%-10s","NO");
            fprintf(outFile,"%-10s",Vir);
            fprintf(outFile,"%-10s\n",Person.ch);
        }
     }
}