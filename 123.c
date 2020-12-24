#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#define MAX_NUM 6000
#define MAX_STR_LEN 10
typedef nt KeyType;
typedef struct
{
	KeyType key;
}RecordType;
typedef struct
{
	RecordType R[MAX_NUM+1];
	int length;
}OrderList;
long compCount;
long moveCount;
OrderList CreateDataRandom(OrderList a)
{
	int n,m,i;
	printf("输入输入的数的最值和个数");
	scanf("%d %d",&n,&m);
	srand((unsigned)time(NULL));
	for(i=1;i<=n;i++)
		a.R[i].key=rand()%m+1;
	a.length=n;
	return a;
}
OrderList CopyList(OrderList a)
{
	OrderList b;
	int i;
	b.length=a.length;
	for(i=1;i<=a.length;i++)
		b.R[i]=a.R[i];
	return b;
}
void InvertedList(OrderList *a)
{
	int i;
	RecordType temp;
	for(i=1;i<a->length/2;i++)
	{
		temp=a->R[i];
		a->R[i]=a->R[a->length-i+1];
		a->R[a->length-i+1]=temp;
	}
}
int Less(int x,int y)
{
	comCount++;
	return x<y;
}
int LessOrEqual(int x,int y)
{
	compCount++;
	return (x<=y);
}
void Swap(OrderList *L,int i,int j)
{
	RecordType temp;
	temp=L->R[i];
	L->R[i]=L->R[j];
	L->R[j]=temp;
	moveCount+=3;
}
void OutputData(OrderList a)
{
	int i;
	for(i=1i<=a.length;i++)
	{
		printf("%4d",a.R[i].key);
		if((i%10)==0)
			pritnf("\n");
	}
}
OrderList InsertSort(OrderList L)
{
	int i,j;
	for(i=2;i<=L.length;i++)
	{
		L.R[0]=L.R[i];
		j=i-1;
		while(Less(L.R[0].key,L.R[j].key))
		{
			L.R[j+1]=L.R[j];
			moveCount++;
			j--;
		}
		L.R[j+1]=L.R[0];
	}
	return L;
}
OrderList ShellSort(OrderList L)
{
	int i,j,d;
	RecordType temp;
	for(d=L.length/2;d>0;d/=2)
	{
		for(i=d+1;i<=L.length;i++)
		{
			temp=L.R[i];
			j=i-d;
			while(j>=1&&Less(temp.key,L.R[j].key))
			{
				L.R[j+d]=L.R[j];
				moveCount++;
				j=j-d;
			}
			L.R[j+d]=temp;
		}
	}
	return L;
}
OrderList BubbleSort(OrderList L)
{
	int i,j;
	int flag;
	for(j=1;j<=L.length-1;j++)
	{
		flag=0;
		for(i=1;i<=L.length-j;i++)
		if(Less(L.R[i+1].key,L.R[i].key))
		{
			Swap[&L,i+1,i]
			flag=1;
		}
		if(flag==0)
			break;
	}
	return L;
}