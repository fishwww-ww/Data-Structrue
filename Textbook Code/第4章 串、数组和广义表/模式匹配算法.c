#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxlen 255

//串的定长顺序存储
typedef struct
{
    char ch[maxlen+1];
    int length;
}SString;

int next[maxlen];

//计算next函数值
void get_next(SString t,int *next)
{
    int i=1;
    int j=0;
    next[1]=0;
    while (i<t.length)
    {
        if(j==0 || t.ch[i]==t.ch[j]){
            i++;
            j++;
            next[i]=j;
        }
        else{
            j=next[j];
        }
    }
}

//计算next函数修正值
void get_nextval(SString t,int nextval[])
{
    int i=1;
    int j=0;
    nextval[1]=0;
    while (i<t.length)
    {
        if(j==0 || t.ch[i]==t.ch[j]){
            i++;
            j++;
            if(t.ch[i]!=t.ch[j]) nextval[i]=j;       //两个字符不等时，无需修正，与get_next函数相同
            else nextval[i]=nextval[j];              //两个字符相等时，令nextval值也相等
        }
        else j=nextval[j];
    }
}

//KMP算法
int Index_KMP(SString s,SString t,int pos)
{
    int i=pos;
    int j=1;
    
    get_nextval(t,next);
    while(i<=s.length && j<=t.length){ //两串都未退到最后
        if(j==0 || s.ch[i]==t.ch[j]){
            i++;
            j++;
        }
        else{
            j=next[j];
        }
    }
    if(j>t.length){
        return i-t.length;
    }
    else{
        return -1;                                         //跳入这儿
    }
}

int main()
{
    //初始化s,t
    // SString *s=(SString *)malloc(sizeof(SString));
    // strcpy(s->ch,"ababcabcacbab");
    // s->length=strlen(s->ch);
    // SString *t=(SString *)malloc(sizeof(SString));
    // strcpy(t->ch,"abcac");
    // t->length=strlen(t->ch);

    SString s;
    // ababcabcacbab
    strcpy(s.ch,"ababcabcacb");                          //bug：主串的模式串后不能有其他字符，否则会跳入else分支返回-1
    s.length=strlen(s.ch);
    SString t;
    strcpy(t.ch,"abcac");
    t.length=strlen(t.ch);
    get_next(t,next);
    //printf("%s\n%d\n%s\n%d\n",s.ch,s.length,t.ch,t.length);
    printf("%d",Index_KMP(s,t,0));
    return 0;
}

// //BF算法
// int Index_BF(SString s,SString t,int pos)
// {
//     int i=pos;
//     int j=1;
//     while (i<=s.length && j<=t.length)
//     {
//         if(s.ch[i]==t.ch[j]){
//             i++;
//             j++;
//         }
//         else{
//             i=i-j+2;
//             j=1;
//         }
//     }
//     if(j>t.length){
//         return i-t.length;
//     }
//     else{
//         return 0;
//     }   
// }