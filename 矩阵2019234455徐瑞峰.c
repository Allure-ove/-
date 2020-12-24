#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define MAXSIZE 100          /*�������Ԫ���������ֵΪ100*/
#define MAXMU 25              /*ϡ������������ֵΪ25*/
typedef struct
{
	int i,j;                 /*�÷���Ԫ�����±�����±�*/
	int v;
}Triple;
typedef struct            /*ϡ�����������Ԫ���˳��洢*/
{   int rpos[MAXMU+1];	     /*���е�һ������Ԫ�ص�λ�ñ�*/
	Triple data[MAXSIZE+1];  /*����Ԫ��Ԫ��˳���,data[0]δʹ��*/
	int mu,nu,tu;            /*���������,�����ͷ���Ԫ����*/
}TSMatrix;
void creat(TSMatrix *T) /*���û����봴��ϡ�����*/
{
	int row,num,k;
	do
	{
		printf("\n ���������\n");
		printf("*********************************\n");
		printf(" ������ϡ���������: ");
		scanf("%d", &T->mu);
		if (T->mu<0 || T->mu>MAXMU)
			printf("\n �����������巶Χ,����������!\n");
	} while (T->mu<0 || T->mu>MAXMU);
	do
	{
		printf(" ������ϡ���������: ");
		scanf("%d", &T->nu);
		if (T->nu<0 || T->nu>MAXMU)
			printf("\n �����������巶Χ,����������!\n");
	} while (T->nu<0 || T->nu>MAXMU);
	do
	{
		printf(" ������ϡ�����ķ���Ԫ�ظ���: ");
		scanf("%d", &T->tu);
		if (T->tu>MAXSIZE || (T->tu>T->mu*T->nu))
			printf("\n ����Ԫ�ظ����������巶Χ,����������!\n");
	} while (T->tu>MAXSIZE || (T->tu>T->mu*T->nu));
	printf(" �밴�д�С����������������Ϣ!\n");
	for (k=1; k<=T->tu; k++)
	{
		do
		{
			printf(" �밴��Ԫ��洢�����%d������Ԫ�ص�����i:", k);
			scanf("%d", &T->data[k].i);
		} while ((!T->data[k].i || T->data[k].i>T->mu));
		do
		{
			printf(" �밴��Ԫ��洢�����%d������Ԫ�ص�����j:", k);
			scanf("%d", &T->data[k].j);
		} while ((!T->data[k].j || T->data[k].j>T->nu));
		do
		{
			printf(" �밴��Ԫ��洢�����%d������Ԫ�ص�ֵv:", k);
			scanf("%d", &T->data[k].v);
		} while (T->data[k].v==0);
	}
	for(row=1,num=1;row<=T->mu;row++)   /*���߼�������Ϣ�洢*/
	{
		T->rpos[row]=num;
		while(T->data[num].i==row)
			num++;
	}
	return;
}

void print(TSMatrix A)   /*���ϡ�����*/
{
	int q,n,k,a=0;
    printf("\n\n����ϡ��������������㣬���ý��Ϊ��\n");
    printf("***********************************\n");
    printf("***********************************\n");
	for(n=1;n<=A.mu;n++)
	{
	 for(k=1;k<=A.nu;k++)
       {
		 for(q=1;q<=A.tu;q++)
			 if(A.data[q].i==n && A.data[q].j==k)
			 {
				 printf("\t%-3d",A.data[q].v);break;
			 }
		 if(q>A.tu)
			 printf("\t%-3d",a);		 
	   }
	 printf("\n");
	} 
	printf("***********************************\n");
	printf("***********************************\n");
 }

void add(TSMatrix A,TSMatrix B)   /*�ӷ�����*/
{
	int n,k;
	if(A.mu!=B.mu || A.nu!=B.nu)
	{ 
		printf("\n          ����������������!"); 
        printf("\n ���������������������������Ӧ��ȷ��ɽ��мӷ����㣡��");
	}
	else  
	{
		for(n=1;n<=A.tu;n++)
	         for(k=1;k<=B.tu;k++)   /*������A�ķ���Ԫ����B��*/
				 if(A.data[n].i==B.data[k].i && A.data[n].j==B.data[k].j)
				 {
					 A.data[n].v+=B.data[k].v;
			         B.data[k].v=0;
				 }
		for(k=1;k<=B.tu;k++)
			if(B.data[k].v!=0)
			{
				A.data[A.tu+1].i=B.data[k].i;
				A.data[A.tu+1].j=B.data[k].j;
				A.data[A.tu+1].v=B.data[k].v;
				A.tu++;	
			}
		print(A);
     }
}

void sub(TSMatrix A,TSMatrix B)   /*��������*/
{
	int n,k;
    if(A.mu!=B.mu || A.nu!=B.nu)
	{
		printf("\n    ����������������!"); 
		printf("\n ��Ҫ�������������������������Ӧ��ȷ��ɽ��м������㣡��");
	}
	else
	{
	    for(n=1;n<=A.tu;n++)
	        for(k=1;k<=B.tu;k++)   /*������A�ķ���Ԫ����B��*/
				if(A.data[n].i==B.data[k].i && A.data[n].j==B.data[k].j)
				{
					A.data[n].v-=B.data[k].v;
					B.data[k].v=0;
				}
            for(k=1;k<=B.tu;k++)
				if(B.data[k].v!=0)
				{
					A.data[A.tu+1].i=B.data[k].i;
				    A.data[A.tu+1].j=B.data[k].j;
				    A.data[A.tu+1].v=-B.data[k].v;
				    A.tu++;
				}
		print(A);  
	}
}

void mult(TSMatrix A,TSMatrix B,TSMatrix *c)   /*�˷�����*/
{
	int arow,tp,i,t;
	int ccol,p,brow,q;
	int ctemp[MAXMU+1];
	if(A.nu!=B.mu)
	{
		printf(" �����������������");
		return ;
	}
	c->mu=A.mu;
	c->nu=B.nu;
	c->tu=0;
	if(A.tu==0||B.tu==0)
	{
		printf(" �������Ϊ�㣡");
		return ;
	}
	else
	{
		for(arow=1;arow<=A.mu;arow++)
		{
			for(i=0;i<MAXMU;i++)    /*�洢������*/
				ctemp[i]=0;
			c->rpos[arow]=c->tu+1;
			if(arow<A.mu)
				tp=A.rpos[arow+1];
			else
				tp=A.tu+1;
			for(p=A.rpos[arow];p<tp;p++)
			{
				brow=A.data[p].j;
				if(brow<B.mu)
					t=B.rpos[brow+1];
				else
					t=B.tu+1;
				for(q=B.rpos[brow];q<t;q++)
				{
					ccol=B.data[q].j;
					ctemp[ccol]+=A.data[p].v*B.data[q].v;
				}
			}
			for(ccol=1;ccol<=c->nu;ccol++)
				if(ctemp[ccol])
				{
					if(++(c->tu)>MAXSIZE)
					{
						printf("������Χ��");
						return ;
					}
				    c->data[c->tu].v=ctemp[ccol];
				    c->data[c->tu].i=arow;
				    c->data[c->tu].j=ccol;
				}
		}
	}
	print(*c);
}
char menu()   /*�����������棨�˵���*/
{
	char n;
    printf("              ****************************************          \n");
    printf("              *                                      *          \n");
    printf("              *         ϡ �� �� �� �� �� ��         *          \n");
    printf("              *                                      *          \n");
    printf("              *             1:�������               *          \n");
    printf("              *             2:�������p               *          \n");
    printf("              *             3:�������               *          \n");
	printf("              *             4:����ת��               *          \n");
	printf("              *             5:ѡ���˳�               *          \n");
	printf("              *                                      *          \n");
    printf("              ****************************************          \n");
    printf("                        ��������Ž��в���  :)                 \n");
    printf("                                 ");n=getchar();
	 
    return n;
}

void zhuanzhi(TSMatrix A)   /*ת������*/
{
	int p,q,m;
	TSMatrix B;
	B.mu=A.nu; /*��ԭ�����������������Ԫ���������¾���*/
	B.nu=A.mu;
	B.tu=A.tu;
	if(B.tu)
	{
		m=1;
		for(p=1;p<=A.mu;p++)              /*��ԭ����Ԫ��Ԫ�������ֵ�����󸳸�����Ԫ�飬�õ�ת�þ���*/
			for(q=1;q<=A.nu;q++)
			{
				B.data[m].i=A.data[m].j;
				B.data[m].j=A.data[m].i;
				B.data[m].v=A.data[m].v;
				++m;
			}
	}
	print(B);
}

int JsMatrix(int s[][MAXMU],int n) /*ͨ���ݹ�������Ӧ����ʽ��ֵ*/   
{
	int z,j,k,r,total=0;
	int b[MAXMU][MAXMU];
	if(n>2)
	{
		for(z=0;z<n;z++)
			{for(j=0;j<n-1;j++)
				for(k=0;k<n-1;k++)
					if(k>=z) b[j][k]=s[j+1][k+1];
					else b[j][k]=s[j+1][k];
					if(z%2==0) r=s[0][z]*JsMatrix(b,n-1);
					else r=(-1)*s[0][z]*JsMatrix(b,n-1);
			total=total+r;
			}
	}
	else if(n==2) total=s[0][0]*s[1][1]-s[0][1]*s[1][0];
	return total;
}

void yuzishi(int s[][MAXMU],int b[][MAXMU],int n) /*�����ÿ��Ԫ�ض�Ӧ������ʽ*/
{
	int z,j,k,m,l,g,a[MAXMU][MAXMU];
	for(z=0;z<n;z++)
	{
		l=z;
		for(j=0;j<n;j++)
		{	
			m=j;
			for(k=0;k<n-1;k++)
				for(g=0;g<n-1;g++)
				{
					if(g>=m&&k<l) a[k][g]=s[k][g+1];
					else if(k>=l&&g<m)  a[k][g]=s[k+1][g];
				    else if(k>=l&&g>=m) a[k][g]=s[k+1][g+1];
				    else   a[k][g]=s[k][g];
				}	
			b[z][j]=JsMatrix(a,n-1);/*����������ʽ�����������ʽ*/
		}
	}
}

void main() /*����������*/
{ 
	TSMatrix A,B,C;

	 for(;;)
		 switch(menu())
	 {case '1':creat(&A);
               creat(&B);
			   add(A,B);
			   break;
      case '2':creat(&A);
               creat(&B);
			   sub(A,B);
			   break;
      case '3':creat(&A);
               creat(&B);
			   mult(A,B,&C);
			   break;
	  case '4':creat(&A);
		       zhuanzhi(A);
			   break;
      case '5':break;
			  printf("�������ѹرգ���������˳� :)\n");
			  exit(0);
	 }
}