#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 255

//串的定长顺序存储
typedef struct
{
    char ch[MAXLEN+1];
    int length;
}SString;

//BF算法
int Index_BF(SString S,SString T,int pos)
{
    int i=pos;
    int j=0;                                                       //课本代码从1开始作为下标计数，本程序从0开始
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

//利用BF算法实现病毒检测
int main()
{
    SString Virus;                                                 //病毒的DNA序列
    SString Person;                                                //人的DNA序列
    SString temp;                                                  //暂存病毒DNA每次的环状序列
    char Vir[MAXLEN];                                              //暂存病毒的初始DNA序列
    int flag=0;                                                    //用来标识是否匹配，初始为0，匹配后为非0
    int m;                                                         //病毒DNA序列的长度
    int num;                                                       //待检测的任务数
    FILE *inFile=fopen("D:\\病毒感染检测输入数据1.txt","a+");        //输入的数据
    FILE *outFile=fopen("D:\\病毒感染检测输出结果.txt","w+");        //输入的数据
    rewind(inFile);
    fscanf(inFile,"%d",&num);
    while (num--)
    {
        fscanf(inFile,"%s",Virus.ch);                              //读取病毒的序列
        fscanf(inFile,"%s",Person.ch);                             //读取人的序列      
        Virus.length=strlen(Virus.ch);                     
        Person.length=strlen(Person.ch);                     
        temp.length=strlen(Virus.ch);                     
        strcpy(Vir,Virus.ch);
        flag=0;
        m=Virus.length;
        for(int i=m,j=0;j<m;j++)
        {
            Virus.ch[i]=Virus.ch[j];                               //将病毒字符串长度扩大两倍
            i++;
        }
        Virus.ch[2*m]='\0';                                        //添加结束符
        for(int i=0;i<m;i++)                                       //取每个长度为m的病毒DNA环状串temp
        {
            for(int j=0;j<m;j++)
            {
                temp.ch[j]=Virus.ch[i+j];
            }
            temp.ch[m]='\0';                                       //添加结束符
            flag=Index_BF(Person,temp,0);                          //BF算法模式匹配
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