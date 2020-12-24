#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define INFINITY 10000
#define M 20                                                    /*最大顶点数*/
typedef struct {
	int num;                                                    /*景点代号*/
	char name[20];                                              /*景点名称*/
	char intro[200];                                            /*景点简介*/
}vertextype;
typedef int edgtype;                                            /*权值类型*/
typedef struct {											/*校园景点图结构体*/
	int vexNum,edgNum;										/*顶点数和边数*/
	vertextype vexs[M];                                         /*顶点信息域*/
	edgtype edge[M][M];                                         /*邻接矩阵*/
}mgraphtype;
int fangshi;
int menu();                                                     /*主菜单*/
void Create_Map(mgraphtype *g);                                 /*从文件读取信息建立图*/
void Print_Map();                                               /*显示校园景点地图*/
int Judge_Input(int num);                                       /*判断输入的编号是否合理*/
void Search_Location(mgraphtype *g);                            /*景点信息查询*/
void ShortPath(mgraphtype *g);                                  /*求景点间最短路径*/
void Floyd_Print(mgraphtype *g, int sNum, int eNum);            /*递归打印两点间最短路径*/
void Shortpath_Print(mgraphtype *g);                            /*输出并打印两点间的最短路径*/
void Dfs_Print(mgraphtype *g, int sNum, int eNum);              /*深度优先遍历查询两景点间所有路径*/
void Allpath_Print(mgraphtype *g);                              /*查询两顶点间的所有路径并打印*/
void BestPath(mgraphtype *g);                                   /*多顶点间求最佳路径*/
void System_Exit(int *q);                                       /*退出系统*/

/*校园景点图的读取与创建*/
void Create_Map(mgraphtype *g)
{
	int i, j;
	g->vexNum=13;
	g->edgNum=18;
	for (i = 1; i <= g->vexNum; i++)
		g->vexs[i].num=i;
	strcpy(g->vexs[1].name,"职工家属楼");
	strcpy(g->vexs[2].name,"大学生活动中心");
	strcpy(g->vexs[3].name,"餐厅");
	strcpy(g->vexs[4].name,"办公实验楼");
	strcpy(g->vexs[5].name,"四教");
	strcpy(g->vexs[6].name,"五教");
	strcpy(g->vexs[7].name,"二教");
	strcpy(g->vexs[8].name,"图书馆");
	strcpy(g->vexs[9].name,"三教");
	strcpy(g->vexs[10].name,"体育馆");
	strcpy(g->vexs[11].name,"男生宿舍");
	strcpy(g->vexs[12].name,"东操场");
	strcpy(g->vexs[13].name,"落雪湖");
	strcpy(g->vexs[1].intro,"落雪湖");
	strcpy(g->vexs[2].intro,"落雪湖");
	strcpy(g->vexs[3].intro,"落雪湖");
	strcpy(g->vexs[4].intro,"落雪湖");
	strcpy(g->vexs[5].intro,"落雪湖");
	strcpy(g->vexs[6].intro,"落雪湖");
	strcpy(g->vexs[7].intro,"落雪湖");
	strcpy(g->vexs[8].intro,"落雪湖");
	strcpy(g->vexs[9].intro,"落雪湖");
	strcpy(g->vexs[10].intro,"落雪湖");
	strcpy(g->vexs[11].intro,"落雪湖");
	strcpy(g->vexs[12].intro,"落雪湖");
	strcpy(g->vexs[13].intro,"落雪湖");
	for (i = 0; i <= g->vexNum; i++)
		for (j = 0; j <= g->vexNum; j++)
		{
			if (i == j)
				g->edge[i][j] = 0;
			else
				g->edge[i][j] = INFINITY;
		}
		g->edge[1][2]=g->edge[2][1]=1;
		g->edge[2][4]=g->edge[4][2]=2;
		g->edge[2][8]=g->edge[8][2]=3;
		g->edge[2][5]=g->edge[5][2]=4;
		g->edge[3][11]=g->edge[11][3]=5;
		g->edge[3][8]=g->edge[8][3]=6;
		g->edge[4][5]=g->edge[5][4]=7;
		g->edge[5][7]=g->edge[7][5]=8;
		g->edge[5][8]=g->edge[8][8]=9;
		g->edge[6][9]=g->edge[9][6]=10;
		g->edge[7][8]=g->edge[8][7]=11;
		g->edge[7][13]=g->edge[13][7]=12;
		g->edge[7][9]=g->edge[9][7]=13;
		g->edge[9][10]=g->edge[10][9]=14;
		g->edge[11][10]=g->edge[10][11]=15;
		g->edge[11][12]=g->edge[12][11]=16;
		g->edge[11][13]=g->edge[13][11]=17;
		g->edge[12][10]=g->edge[10][12]=18;

}

/*校园景点图的显示*/
void Dis_Map() {
 printf("\n                          *山商东校区校园景点地图一览*\n\n");
    printf("                                                               ⑽体育馆       \n");
    printf("                                 ⑹五教      ⑼三教              ◎------|    \n");
    printf("                                    ◎          ◎---------------|       |    \n");
    printf("                                    |------------|               |       |    \n");
    printf("                                                 |               |------◎    \n");
    printf("                          ⑸四教          ⑺二教 |   （13）落雪湖|   ⑿东操场 \n");
    printf("                          ◎                    ◎     ◎        |       |    \n");
    printf("      ⑷办公实验楼◎-------|------------------—-|------|--------|       |    \n");
    printf("                |          |                     |              ◎-------|    \n");
    printf("                |          |                     |              ⑾ 男生宿舍     \n");
    printf("                |          |                    ◎               |            \n");
    printf("                ◎⑵大学生活动中心             ⑻图书馆          |            \n");
    printf("                |--------------------------------|               |            \n");
    printf("                |                                |---------------◎⑶餐厅        \n");
    printf("                |                                                            \n");
    printf("                ◎⑴ 职工家属楼                                                \n\n");
}

/*景点信息查询*/
void Search_Location(mgraphtype *g) {
	int s;
	do {
		printf("\n请输入你要查找的景点编号：");
		scanf("%d", &s);
	} while (Judge_Input(s));
	printf("\n景点名称：[%s]\n\n", g->vexs[s].name);
	printf("景点简介： %s\n\n", g->vexs[s].intro);
}

/*Floyd算法求两景点间的一条最短的路径*/
int dist[M][M];                                                    /*距离向量*/
int path[M][M];                                                    /*路径向量*/
void ShortPath(mgraphtype *g) {
	int i, j, k;
	for (i = 0; i < g->vexNum; i++)                                /*初始化距离向量矩阵与路径向量矩阵*/
		for (j = 0; j < g->vexNum; j++) {
			dist[i][j] = g->edge[i][j];
			if (i != j && dist[i][j] < INFINITY) path[i][j] = i;
			else path[i][j] = -1;                                  /*-1代表当前两点不可达*/
		}
	for (k = 0; k < g->vexNum; k++)                                /*递推求解每两景点的最短路径*/
		for (i = 0; i < g->vexNum; i++)
			for (j = 0; j < g->vexNum; j++)                        /*更新dist[i][j]的值*/
				if (dist[i][j] >(dist[i][k] + dist[k][j])) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;                                /*path用于记录最短路径上的经结点*/
				}
}

/*递归实现打印两点间的最短路径*/
void Floyd_Print(mgraphtype *g, int sNum, int eNum) {
	if (path[sNum][eNum] == -1 || path[sNum][eNum] == eNum || path[sNum][eNum] == sNum)
		return;
	else {
		Floyd_Print(g, sNum, path[sNum][eNum]);                 /*将中间点作为终点继续打印路径*/
		printf("%s->", g->vexs[path[sNum][eNum]].name);         /*打印中间景点名字*/
		Floyd_Print(g, path[sNum][eNum], eNum);                 /*将中间点作为起点继续打印路径*/
	}
}

/*输出并打印两点间的最短路径*/
void Shortpath_Print(mgraphtype *g) {
	int sNum, eNum;                                             /*起点编号，终点编号*/
	do {
		printf("\n请输入起点编号：");
		scanf("%d", &sNum);
	} while (Judge_Input(sNum));
	do {
		printf("\n请输入终点编号：");
		scanf("%d", &eNum);
	} while (Judge_Input(eNum));
	printf("\n%s到%s的最短距离是：%dm\n", g->vexs[sNum].name, g->vexs[eNum].name, dist[sNum][eNum]);
	printf("\n这是最佳游览路线：");
	printf("%s->", g->vexs[sNum].name);                                       /*输出路径上的起点*/
	Floyd_Print(g, sNum, eNum);                                               /*输出路径上的中间点*/
	printf("%s\n\n", g->vexs[eNum].name);                                     /*输出路径上的终点*/
}

/*深度优先遍历查询任意两个景点之间的所有路径*/
int pathStack[M];                                                             /*路径栈，存储路径信息*/
int top;                                                                      /*栈顶*/
int visited[M];                                                               /*入栈标记，防止形成回路*/
int count;                                                                    /*路径计数器*/
void Dfs_Print(mgraphtype *g, int sNum, int eNum) {
	int dis = 0,i,j;                                                              /*用于记录路径长度*/
	pathStack[top] = sNum;                                                    /*将本趟起点入栈*/
	top++;
	visited[sNum] = 1;                                                        /*将入栈点标记为已入栈*/
	for (i = 1; i <= g->vexNum; i++) {
		if (g->edge[sNum][i] > 0 && g->edge[sNum][i] != INFINITY && !visited[i]) {
			/*表明前一个入栈点与该点可达，且该点未入栈（未被访问）*/
			if (i == eNum) {                                                  /*如果深度遍历搜到了终点，就输出刚才的路径*/
				printf("第%d条路:", count++);
				for ( j = 0; j < top; j++) 
				{
					printf("%s->", g->vexs[pathStack[j]].name);
					if (j < top - 1)
						dis = dis + g->edge[pathStack[j]][pathStack[j + 1]];        /*统计路径长度*/
				}
				dis = dis + g->edge[pathStack[top - 1]][eNum];                      /*最后一条路单独出来，因为enum不能入栈*/
				printf("%s\n", g->vexs[eNum].name);
				printf("总长度是：%dm\n\n", dis);
			}
			else {
				Dfs_Print(g, i, eNum);                                              /*如果该点不是终点,接着深度搜索*/
				top--;                                                              /*支路全被访问一遍后，顶点出栈*/
				visited[i] = 0;                                                     /*将出栈点标记为已出栈，允许下次访问*/
			}
		}
	}
}

/*查询任意两个景点之间的所有路径并打印*/
void Allpath_Print(mgraphtype *g) {
	int sNum, eNum;
	count = 1;                                                       /*路径计数器*/
	top = 0;                                                         /*栈顶*/
	memset(pathStack, 0, sizeof(pathStack));                         /*路径栈初始化*/
	memset(visited, 0, sizeof(visited));                             /*入栈标记初始化*/
	do {
		printf("\n请输入起点编号：");
		scanf("%d", &sNum);
	} while (Judge_Input(sNum));
	do {
		printf("\n请输入终点编号：");
		scanf("%d", &eNum);
	} while (Judge_Input(eNum));
	printf("\n");
	Dfs_Print(g, sNum, eNum);
}

/*多景点间求最佳路径*/
void BestPath(mgraphtype *g) {
	int vNum[M] = { 0 }, j = 1;                                       /*记录用户输入的编号信息*/
	int d = 0,i;                                                        /*统计全程总长*/
	printf("\n请输入你要游览的第%d个景点的编号（输入-1结束输入）：", j);
	scanf("%d", &vNum[j - 1]);
	while (vNum[j - 1] != -1 && j < 12) 
	{
		while (Judge_Input(vNum[j - 1])) 
		{
			printf("\n请输入你要游览的第%d个景点编号：", ++j);
			scanf("%d", &vNum[j - 1]);
		}
		if (vNum[j - 1] == -1) break;
		printf("\n请输入你要游览的第%d个景点编号：", ++j);
		scanf("%d", &vNum[j - 1]);
	}
	printf("\n这是最佳访问路径：");
	for ( i = 0; vNum[i] > 0 && vNum[i + 1] > 0; i++)
	{
		printf("%s->", g->vexs[vNum[i]].name);                   /*输出路径上的起点*/
		Floyd_Print(g, vNum[i], vNum[i + 1]);                /*利用Floyd算法*/
		d += dist[vNum[i]][vNum[i + 1]];
	}
	printf("%s\n\n", g->vexs[vNum[j - 2]].name);                 /*输出路径上的终点*/
	printf("全程总长为：%dm\n\n", d);
}

/*主菜单*/
int menu() {
	int s;
	printf("\t\t			 欢迎使用山东工商学院导游咨询系统 \n");
	printf("\t\t    1.山东工商学院景点信息查询			 2.两景点间最短路径查询 \n");
	printf("\t\t    3.两景点间所有路径查询			 4.多景点间访问路线查询 \n");
	printf("\t\t    5.退出校园导游咨询系统 \n");
	printf("\t\t请根据你的需求选择操作：");
	scanf("%d", &s);
	printf("\n\n");
	return s;
}
/*判断输入的编号是否合理*/
int Judge_Input(int num)
{
	int i = 0;
	if (num == -1)
		return i;
	if (num < 1 || num>13)
	{
		printf("\n输入的编号有误，请输入1-13之间的数字！\n");
		i = 1;
	}

	return i;
}
/*退出菜单栏*/
void System_Exit(int *quit) {
	*quit = 1;
	printf("\t\t                ┌───────────────────┐                \n");
	printf("\t\t              ├──        欢迎下次使用，谢谢！      ──┤              \n");
	printf("\t\t                └───────────────────┘                \n");
	printf("\t\t                  *     *        *       *         * * *                  \n");
	printf("\t\t                  * *   *        *       *       *       *                \n");
	printf("\t\t                  *  *  *        *       *       *       *                \n");
	printf("\t\t                  *   * *        *       *       *       *                \n");
	printf("\t\t                  *     *          * * *           * * *                  \n");
}

/*主函数*/
int main() {
	int quit = 0;
	mgraphtype g;
	Create_Map(&g);
	ShortPath(&g);                                                               /*Floyd求出dist与path*/
		while (!quit)
		{																		/*系统退出条件满足判定*/
			switch (menu()) 
			{                                                    /*打印主菜单*/
				case 1:system("cls"); Dis_Map(); Search_Location(&g); break;         /*中北校园景点信息查询*/
				case 2:system("cls"); Dis_Map(); Shortpath_Print(&g); break;         /*两景点间最短路径查询*/
				case 3:system("cls"); Dis_Map(); Allpath_Print(&g); break;           /*两景点间所有路径查询*/
				case 4:system("cls"); Dis_Map(); BestPath(&g); break;                /*多景点间访问路线查询*/
						 /*公告栏查看*/
				case 6:system("cls"); System_Exit(&quit); break;                     /*退出校园导游咨询系统*/
				default:printf("\t\t\t\t\t错误！没有该选项对应的操作。\n\n");
			}
			system("pause");
			system("cls");                                                           /*清屏*/
		}
		return 0;
}
