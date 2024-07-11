#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

//ͼ��ṹ�嶨��
typedef struct Book
{
    char ISBN[20];
    char name[50];
    float price;
}Book;

//�˸����ܺ���
void createAndOutput(Book *book);             //�������������
void update(Book *book);                      //�޸ĺ���
void invertOrder(Book *book);                 //����洢
void seekMostExpensive(Book *book);           //�������ͼ��  
int compare(const void*a,const void*b);       //seekMostExpensive����������ʽ  
void newBookIn(Book *book);                   //��ͼ�����  
void oldBookOut(Book *book);                  //��ͼ�����  
void deleteRepeat(Book *book);                //ͼ��ȥ��  

//����ȫ�ֱ���
int length=0;                                 //��¼��ӵ��鱾������
float sumPrice=0.0;                           //���ͼ���ܼ�


int main()
{
    Book book[max];
    int handle;
    printf("������������ѡ�����²�����\n");
    printf("0.�˳�ϵͳ\n");
    printf("1.���������\n");
    printf("2.�޸�ͼ����Ϣ\n");
    printf("3.����洢\n");
    printf("4.�������ͼ��\n");
    printf("5.��ͼ�����\n");
    printf("6.��ͼ�����\n");
    printf("7.ͼ��ȥ��\n");
    scanf("%d",&handle);
    switch (handle){
        case 0:
            printf("���ѳɹ��˳�ϵͳ\n");
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
            printf("�����������Ч���֣���������Ч���֣�\n");
            break;
    }
    return 0;
}

//�������������
void createAndOutput(Book *book)
{
    int bookNumber=0;
    Book *temp;//��ʱ�����������
    for(;length<max;length++){
        scanf("%s",(temp->ISBN));
        scanf("%s",(temp->name));
        scanf("%f",&(temp->price));
        getchar();
        //��ֹѭ��
        if(strcmp(temp->ISBN,"0")==0 && strcmp(temp->name,"0")==0 && temp->price==0){
            break;
        }
        //�ݴ����ݸ�ֵ��book
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

//�޸ĺ���
void update(Book *book)
{
    int bookNumber=0;
    Book *temp;//��ʱ�����������
    for(;length<max;length++){
        scanf("%s",(temp->ISBN));
        scanf("%s",(temp->name));
        scanf("%f",&(temp->price));
        //��ֹѭ��
        if(*(temp->ISBN)=='0'&&*(temp->name)=='0'&&temp->price==0.0){
            break;
        }
        //�ݴ����ݸ�ֵ��book
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

//����洢
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

//���ͼ�����
void seekMostExpensive(Book *book)
{
    int bookNumber;
    scanf("%d",&bookNumber);
    Book orderedBook[bookNumber];//����ṹ������
    length=bookNumber;
    for(int i=bookNumber-1;i>=0;i--){
        scanf("%s%s%f",(book+i)->ISBN,(book+i)->name,&(book+i)->price);
        *(orderedBook+i)=*(book+i);
    }
    qsort(orderedBook,bookNumber,sizeof(Book),compare);//������ṹ������Ӵ�С����
    int mostExpensiveNum=1;
    //ͳ�����ͼ������
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

//seekMostExpensive����������ṹ�����������ʽ
int compare(const void*a,const void*b)
{
    return ((Book *)b)->price-((Book *)a)->price;
}

//��ͼ�����
void newBookIn(Book *book)
{
    int bookNumber;
    scanf("%d",&bookNumber);
    length=bookNumber;
    for(int i=0;i<bookNumber;i++){
        scanf("%s%s%f",(book+i)->ISBN,(book+i)->name,&(book+i)->price);
    }
    Book newBook;//��������ͼ��
    int location;//���λ��
    scanf("%d",&location);
    scanf("%s%s%f",newBook.ISBN,newBook.name,&(newBook.price));
    //�ж����λ���Ƿ�Ϸ�
    if((location<1)||(location>length+1)||(length==max)){
        printf("��Ǹ�����λ�÷Ƿ���\n");
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

//��ͼ�����
void oldBookOut(Book *book)
{
    int bookNumber;
    scanf("%d",&bookNumber);
    length=bookNumber;
    for(int i=0;i<bookNumber;i++){
        scanf("%s%s%f",(book+i)->ISBN,(book+i)->name,&(book+i)->price);
    }
    int location;//����λ��
    scanf("%d",&location);
    //�жϳ���λ���Ƿ�Ϸ�
    if((location<1)||(location>length)){
        printf("��Ǹ������λ�÷Ƿ���\n");
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

//ͼ��ȥ��
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
			    //���� 
	  	        *(book+j)=*(book+j+1); //�Ѵӵ�j��Ԫ��֮���ǰ�� 
	  	        length--;
	  	   	}
	  	}   
    }
    printf("%d\n",length);
    for(int i=0;i<length;i++){
        printf("%s %s %.2f\n",(book+i)->ISBN,(book+i)->name,(book+i)->price);
    }
}