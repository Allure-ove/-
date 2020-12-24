#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define MAXSIZE 100          /*假设非零元个数的最大值为100*/
#define MAXMU 25              /*稀疏矩阵最大行列值为25*/
typedef struct
{
	int i,j;                 /*该非零元的行下标和列下标*/
	int v;
}Triple;
typedef struct            /*稀疏矩阵是由三元组的顺序存储*/
{   int rpos[MAXMU+1];	     /*各行第一个非零元素的位置表*/
	Triple data[MAXSIZE+1];  /*非零元三元组顺序表,data[0]未使用*/
	int mu,nu,tu;            /*矩阵的行数,列数和非零元个数*/
}TSMatrix;
void creat(TSMatrix *T) /*由用户输入创建稀疏矩阵*/
{
	int row,num,k;
	do
	{
		printf("\n 请输入矩阵！\n");
		printf("*********************************\n");
		printf(" 请输入稀疏矩阵行数: ");
		scanf("%d", &T->mu);
		if (T->mu<0 || T->mu>MAXMU)
			printf("\n 行数超出定义范围,请重新输入!\n");
	} while (T->mu<0 || T->mu>MAXMU);
	do
	{
		printf(" 请输入稀疏矩阵列数: ");
		scanf("%d", &T->nu);
		if (T->nu<0 || T->nu>MAXMU)
			printf("\n 列数超出定义范围,请重新输入!\n");
	} while (T->nu<0 || T->nu>MAXMU);
	do
	{
		printf(" 请输入稀疏矩阵的非零元素个数: ");
		scanf("%d", &T->tu);
		if (T->tu>MAXSIZE || (T->tu>T->mu*T->nu))
			printf("\n 非零元素个数超出定义范围,请重新输入!\n");
	} while (T->tu>MAXSIZE || (T->tu>T->mu*T->nu));
	printf(" 请按行从小到大依次输入结点信息!\n");
	for (k=1; k<=T->tu; k++)
	{
		do
		{
			printf(" 请按三元组存储输入第%d个非零元素的行数i:", k);
			scanf("%d", &T->data[k].i);
		} while ((!T->data[k].i || T->data[k].i>T->mu));
		do
		{
			printf(" 请按三元组存储输入第%d个非零元素的列数j:", k);
			scanf("%d", &T->data[k].j);
		} while ((!T->data[k].j || T->data[k].j>T->nu));
		do
		{
			printf(" 请按三元组存储输入第%d个非零元素的值v:", k);
			scanf("%d", &T->data[k].v);
		} while (T->data[k].v==0);
	}
	for(row=1,num=1;row<=T->mu;row++)   /*行逻辑链接信息存储*/
	{
		T->rpos[row]=num;
		while(T->data[num].i==row)
			num++;
	}
	return;
}

void print(TSMatrix A)   /*输出稀疏矩阵*/
{
	int q,n,k,a=0;
    printf("\n\n经过稀疏矩阵运算器运算，所得结果为：\n");
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

void add(TSMatrix A,TSMatrix B)   /*加法运算*/
{
	int n,k;
	if(A.mu!=B.mu || A.nu!=B.nu)
	{ 
		printf("\n          不满足矩阵相加条件!"); 
        printf("\n 需满足两矩阵的行数、列数均对应相等方可进行加法运算！！");
	}
	else  
	{
		for(n=1;n<=A.tu;n++)
	         for(k=1;k<=B.tu;k++)   /*将矩阵A的非零元接至B中*/
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

void sub(TSMatrix A,TSMatrix B)   /*减法运算*/
{
	int n,k;
    if(A.mu!=B.mu || A.nu!=B.nu)
	{
		printf("\n    不满足矩阵相减条件!"); 
		printf("\n 需要满足两矩阵的行数、列数均对应相等方可进行减法运算！！");
	}
	else
	{
	    for(n=1;n<=A.tu;n++)
	        for(k=1;k<=B.tu;k++)   /*将矩阵A的非零元接至B中*/
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

void mult(TSMatrix A,TSMatrix B,TSMatrix *c)   /*乘法运算*/
{
	int arow,tp,i,t;
	int ccol,p,brow,q;
	int ctemp[MAXMU+1];
	if(A.nu!=B.mu)
	{
		printf(" 矩阵不满足相乘条件！");
		return ;
	}
	c->mu=A.mu;
	c->nu=B.nu;
	c->tu=0;
	if(A.tu==0||B.tu==0)
	{
		printf(" 结果矩阵为零！");
		return ;
	}
	else
	{
		for(arow=1;arow<=A.mu;arow++)
		{
			for(i=0;i<MAXMU;i++)    /*存储器清零*/
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
						printf("超出范围！");
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
char menu()   /*计算器主界面（菜单）*/
{
	char n;
    printf("              ****************************************          \n");
    printf("              *                                      *          \n");
    printf("              *         稀 疏 矩 阵 运 算 器         *          \n");
    printf("              *                                      *          \n");
    printf("              *             1:矩阵相加               *          \n");
    printf("              *             2:矩阵相減               *          \n");
    printf("              *             3:矩阵相乘               *          \n");
	printf("              *             4:矩阵转置               *          \n");
	printf("              *             5:选择退出               *          \n");
	printf("              *                                      *          \n");
    printf("              ****************************************          \n");
    printf("                        请输入序号进行操作  :)                 \n");
    printf("                                 ");n=getchar();
	 
    return n;
}

void zhuanzhi(TSMatrix A)   /*转置运算*/
{
	int p,q,m;
	TSMatrix B;
	B.mu=A.nu; /*将原矩阵的行列数及非零元个数赋给新矩阵*/
	B.nu=A.mu;
	B.tu=A.tu;
	if(B.tu)
	{
		m=1;
		for(p=1;p<=A.mu;p++)              /*将原非零元三元组的行列值交换后赋给新三元组，得到转置矩阵*/
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

int JsMatrix(int s[][MAXMU],int n) /*通过递归求矩阵对应行列式的值*/   
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

void yuzishi(int s[][MAXMU],int b[][MAXMU],int n) /*求矩阵每个元素对应的余子式*/
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
			b[z][j]=JsMatrix(a,n-1);/*调用求行列式函数求出余子式*/
		}
	}
}

void main() /*功能主函数*/
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
			  printf("计算器已关闭，按任意键退出 :)\n");
			  exit(0);
	 }
}