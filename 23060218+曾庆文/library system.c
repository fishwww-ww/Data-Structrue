#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

//图书结构体定义
typedef struct Book
{
    char ISBN[20];
    char name[50];
    float price;
}Book;

//八个功能函数
void createAndOutput(Book *book);             //创建和输出函数
void update(Book *book);                      //修改函数
void invertOrder(Book *book);                 //逆序存储
void seekMostExpensive(Book *book);           //查找最贵图书  
int compare(const void*a,const void*b);       //seekMostExpensive函数的排序方式  
void newBookIn(Book *book);                   //新图书入库  
void oldBookOut(Book *book);                  //旧图书出库  
void deleteRepeat(Book *book);                //图书去重  

//两个全局变量
int length=0;                                 //记录添加的书本的数量
float sumPrice=0.0;                           //入库图书总价


int main()
{
    Book book[max];
    int handle;
    printf("请输入数字以选择以下操作：\n");
    printf("0.退出系统\n");
    printf("1.创建和输出\n");
    printf("2.修改图书信息\n");
    printf("3.逆序存储\n");
    printf("4.查找最贵图书\n");
    printf("5.新图书入库\n");
    printf("6.旧图书出库\n");
    printf("7.图书去重\n");
    scanf("%d",&handle);
    switch (handle){
        case 0:
            printf("您已成功退出系统\n");
            return 0;
        case 1:
            createAndOutput(book);
            break;
        case 2:
            update(book);
            break;
        case 3:
            invertOrder(book);
            break;
        case 4:
            seekMostExpensive(book);
            break;
        case 5:
            newBookIn(book);
            break;
        case 6:
            oldBookOut(book);
            break;
        case 7:
            deleteRepeat(book);
            break;
        default:
            printf("您输入的是无效数字，请输入有效数字：\n");
            break;
    }
    return 0;
}

//创建和输出函数
void createAndOutput(Book *book)
{
    int bookNumber=0;
    Book *temp;//暂时存放输入数据
    for(;length<max;length++){
        scanf("%s",(temp->ISBN));
        scanf("%s",(temp->name));
        scanf("%f",&(temp->price));
        getchar();
        //终止循环
        if(strcmp(temp->ISBN,"0")==0 && strcmp(temp->name,"0")==0 && temp->price==0){
            break;
        }
        //暂存数据赋值给book
        else{
            *(book+length)=*temp;
            bookNumber++;
        }
    }
    printf("%d\n",bookNumber);
    for(int i=0;i<bookNumber;i++){
        printf("%s %s %.2f",(book+i)->ISBN,(book+i)->name,(book+i)->price);
        printf("\n");
    }
}

//修改函数
void update(Book *book)
{
    int bookNumber=0;
    Book *temp;//暂时存放输入数据
    for(;length<max;length++){
        scanf("%s",(temp->ISBN));
        scanf("%s",(temp->name));
        scanf("%f",&(temp->price));
        //终止循环
        if(*(temp->ISBN)=='0'&&*(temp->name)=='0'&&temp->price==0.0){
            break;
        }
        //暂存数据赋值给book
        else{
            *(book+length)=*temp;
            sumPrice+=temp->price;
            bookNumber++;
        }
    }
    float avePrice=sumPrice/bookNumber;
    printf("%.2f\n",avePrice);
    for(int i=0;i<bookNumber;i++){
        if((book+i)->price<avePrice){
            (book+i)->price*=1.2;
            printf("%s %s %.2f",(book+i)->ISBN,(book+i)->name,(book+i)->price);
            printf("\n");
        }
        else{
            (book+i)->price*=1.1;
            printf("%s %s %.2f",(book+i)->ISBN,(book+i)->name,(book+i)->price);
            printf("\n");
        }
    }
}

//逆序存储
void invertOrder(Book *book)
{
    int bookNumber;
    scanf("%d",&bookNumber);
    length=bookNumber;
    for(int i=bookNumber-1;i>=0;i--){
        scanf("%s%s%f",(book+i)->ISBN,(book+i)->name,&(book+i)->price);
    }
    for(int i=0;i<bookNumber;i++){
        printf("%s %s %.2f\n",(book+i)->ISBN,(book+i)->name,(book+i)->price);
    }
}

//最贵图书查找
void seekMostExpensive(Book *book)
{
    int bookNumber;
    scanf("%d",&bookNumber);
    Book orderedBook[bookNumber];//有序结构体数组
    length=bookNumber;
    for(int i=bookNumber-1;i>=0;i--){
        scanf("%s%s%f",(book+i)->ISBN,(book+i)->name,&(book+i)->price);
        *(orderedBook+i)=*(book+i);
    }
    qsort(orderedBook,bookNumber,sizeof(Book),compare);//对有序结构体数组从大到小排序
    int mostExpensiveNum=1;
    //统计最贵图书数量
    for(int i=0;i<bookNumber-1;i++){
        if((orderedBook+i)->price!=(orderedBook+i+1)->price){
            break;
        }
        mostExpensiveNum++;
    }
    printf("%d\n",mostExpensiveNum);
    for(int i=0;i<mostExpensiveNum;i++){
        printf("%s %s %.2f\n",(orderedBook+i)->ISBN,(orderedBook+i)->name,(orderedBook+i)->price);
    }
}

//seekMostExpensive函数中有序结构体数组的排序方式
int compare(const void*a,const void*b)
{
    return ((Book *)b)->price-((Book *)a)->price;
}

//新图书入库
void newBookIn(Book *book)
{
    int bookNumber;
    scanf("%d",&bookNumber);
    length=bookNumber;
    for(int i=0;i<bookNumber;i++){
        scanf("%s%s%f",(book+i)->ISBN,(book+i)->name,&(book+i)->price);
    }
    Book newBook;//待入库的新图书
    int location;//入库位置
    scanf("%d",&location);
    scanf("%s%s%f",newBook.ISBN,newBook.name,&(newBook.price));
    //判断入库位置是否合法
    if((location<1)||(location>length+1)||(length==max)){
        printf("抱歉，入库位置非法！\n");
        return 0;
    }
    for(int j=length-1;j>=location-1;j--){
        *(book+j+1)=*(book+j);
    }
    *(book+location-1)=newBook;
    length++;
    for(int i=0;i<length;i++){
        printf("%s %s %.2f\n",(book+i)->ISBN,(book+i)->name,(book+i)->price);
    }
}

//旧图书出库
void oldBookOut(Book *book)
{
    int bookNumber;
    scanf("%d",&bookNumber);
    length=bookNumber;
    for(int i=0;i<bookNumber;i++){
        scanf("%s%s%f",(book+i)->ISBN,(book+i)->name,&(book+i)->price);
    }
    int location;//出库位置
    scanf("%d",&location);
    //判断出库位置是否合法
    if((location<1)||(location>length)){
        printf("抱歉，出库位置非法！\n");
        return 0;
    }
    for(int j=location;j<length;j++){
        *(book+j-1)=*(book+j);
    }
    length--;
    for(int i=0;i<length;i++){
        printf("%s %s %.2f\n",(book+i)->ISBN,(book+i)->name,(book+i)->price);
    }
}

//图书去重
void deleteRepeat(Book *book)
{
    int bookNumber;
    scanf("%d",&bookNumber);
    length=bookNumber;
    for(int i=0;i<bookNumber;i++){
        scanf("%s%s%f",(book+i)->ISBN,(book+i)->name,&(book+i)->price);
    }
    for(int i=0;i<length;i++){
	  	for(int j = 1; j<length ; j++){
		    if(strcmp((book+i)->ISBN,(book+j)->ISBN)==0&&i!=j){
			    //查重 
	  	        *(book+j)=*(book+j+1); //把从第j个元素之后的前移 
	  	        length--;
	  	   	}
	  	}   
    }
    printf("%d\n",length);
    for(int i=0;i<length;i++){
        printf("%s %s %.2f\n",(book+i)->ISBN,(book+i)->name,(book+i)->price);
    }
}