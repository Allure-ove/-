#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define INFINITY 10000
#define M 20                                                    /*��󶥵���*/
typedef struct {
	int num;                                                    /*�������*/
	char name[20];                                              /*��������*/
	char intro[200];                                            /*������*/
}vertextype;
typedef int edgtype;                                            /*Ȩֵ����*/
typedef struct {											/*У԰����ͼ�ṹ��*/
	int vexNum,edgNum;										/*�������ͱ���*/
	vertextype vexs[M];                                         /*������Ϣ��*/
	edgtype edge[M][M];                                         /*�ڽӾ���*/
}mgraphtype;
int fangshi;
int menu();                                                     /*���˵�*/
void Create_Map(mgraphtype *g);                                 /*���ļ���ȡ��Ϣ����ͼ*/
void Print_Map();                                               /*��ʾУ԰�����ͼ*/
int Judge_Input(int num);                                       /*�ж�����ı���Ƿ����*/
void Search_Location(mgraphtype *g);                            /*������Ϣ��ѯ*/
void ShortPath(mgraphtype *g);                                  /*�󾰵�����·��*/
void Floyd_Print(mgraphtype *g, int sNum, int eNum);            /*�ݹ��ӡ��������·��*/
void Shortpath_Print(mgraphtype *g);                            /*�������ӡ���������·��*/
void Dfs_Print(mgraphtype *g, int sNum, int eNum);              /*������ȱ�����ѯ�����������·��*/
void Allpath_Print(mgraphtype *g);                              /*��ѯ������������·������ӡ*/
void BestPath(mgraphtype *g);                                   /*�ඥ��������·��*/
void System_Exit(int *q);                                       /*�˳�ϵͳ*/

/*У԰����ͼ�Ķ�ȡ�봴��*/
void Create_Map(mgraphtype *g)
{
	int i, j;
	g->vexNum=13;
	g->edgNum=18;
	for (i = 1; i <= g->vexNum; i++)
		g->vexs[i].num=i;
	strcpy(g->vexs[1].name,"ְ������¥");
	strcpy(g->vexs[2].name,"��ѧ�������");
	strcpy(g->vexs[3].name,"����");
	strcpy(g->vexs[4].name,"�칫ʵ��¥");
	strcpy(g->vexs[5].name,"�Ľ�");
	strcpy(g->vexs[6].name,"���");
	strcpy(g->vexs[7].name,"����");
	strcpy(g->vexs[8].name,"ͼ���");
	strcpy(g->vexs[9].name,"����");
	strcpy(g->vexs[10].name,"������");
	strcpy(g->vexs[11].name,"��������");
	strcpy(g->vexs[12].name,"���ٳ�");
	strcpy(g->vexs[13].name,"��ѩ��");
	strcpy(g->vexs[1].intro,"��ѩ��");
	strcpy(g->vexs[2].intro,"��ѩ��");
	strcpy(g->vexs[3].intro,"��ѩ��");
	strcpy(g->vexs[4].intro,"��ѩ��");
	strcpy(g->vexs[5].intro,"��ѩ��");
	strcpy(g->vexs[6].intro,"��ѩ��");
	strcpy(g->vexs[7].intro,"��ѩ��");
	strcpy(g->vexs[8].intro,"��ѩ��");
	strcpy(g->vexs[9].intro,"��ѩ��");
	strcpy(g->vexs[10].intro,"��ѩ��");
	strcpy(g->vexs[11].intro,"��ѩ��");
	strcpy(g->vexs[12].intro,"��ѩ��");
	strcpy(g->vexs[13].intro,"��ѩ��");
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

/*У԰����ͼ����ʾ*/
void Dis_Map() {
 printf("\n                          *ɽ�̶�У��У԰�����ͼһ��*\n\n");
    printf("                                                               ��������       \n");
    printf("                                 �����      ������              ��------|    \n");
    printf("                                    ��          ��---------------|       |    \n");
    printf("                                    |------------|               |       |    \n");
    printf("                                                 |               |------��    \n");
    printf("                          ���Ľ�          �˶��� |   ��13����ѩ��|   �ж��ٳ� \n");
    printf("                          ��                    ��     ��        |       |    \n");
    printf("      �Ȱ칫ʵ��¥��-------|------------------��-|------|--------|       |    \n");
    printf("                |          |                     |              ��-------|    \n");
    printf("                |          |                     |              �� ��������     \n");
    printf("                |          |                    ��               |            \n");
    printf("                ��ƴ�ѧ�������             ��ͼ���          |            \n");
    printf("                |--------------------------------|               |            \n");
    printf("                |                                |---------------��ǲ���        \n");
    printf("                |                                                            \n");
    printf("                ��� ְ������¥                                                \n\n");
}

/*������Ϣ��ѯ*/
void Search_Location(mgraphtype *g) {
	int s;
	do {
		printf("\n��������Ҫ���ҵľ����ţ�");
		scanf("%d", &s);
	} while (Judge_Input(s));
	printf("\n�������ƣ�[%s]\n\n", g->vexs[s].name);
	printf("�����飺 %s\n\n", g->vexs[s].intro);
}

/*Floyd�㷨����������һ����̵�·��*/
int dist[M][M];                                                    /*��������*/
int path[M][M];                                                    /*·������*/
void ShortPath(mgraphtype *g) {
	int i, j, k;
	for (i = 0; i < g->vexNum; i++)                                /*��ʼ����������������·����������*/
		for (j = 0; j < g->vexNum; j++) {
			dist[i][j] = g->edge[i][j];
			if (i != j && dist[i][j] < INFINITY) path[i][j] = i;
			else path[i][j] = -1;                                  /*-1����ǰ���㲻�ɴ�*/
		}
	for (k = 0; k < g->vexNum; k++)                                /*�������ÿ����������·��*/
		for (i = 0; i < g->vexNum; i++)
			for (j = 0; j < g->vexNum; j++)                        /*����dist[i][j]��ֵ*/
				if (dist[i][j] >(dist[i][k] + dist[k][j])) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;                                /*path���ڼ�¼���·���ϵľ����*/
				}
}

/*�ݹ�ʵ�ִ�ӡ���������·��*/
void Floyd_Print(mgraphtype *g, int sNum, int eNum) {
	if (path[sNum][eNum] == -1 || path[sNum][eNum] == eNum || path[sNum][eNum] == sNum)
		return;
	else {
		Floyd_Print(g, sNum, path[sNum][eNum]);                 /*���м����Ϊ�յ������ӡ·��*/
		printf("%s->", g->vexs[path[sNum][eNum]].name);         /*��ӡ�м侰������*/
		Floyd_Print(g, path[sNum][eNum], eNum);                 /*���м����Ϊ��������ӡ·��*/
	}
}

/*�������ӡ���������·��*/
void Shortpath_Print(mgraphtype *g) {
	int sNum, eNum;                                             /*����ţ��յ���*/
	do {
		printf("\n����������ţ�");
		scanf("%d", &sNum);
	} while (Judge_Input(sNum));
	do {
		printf("\n�������յ��ţ�");
		scanf("%d", &eNum);
	} while (Judge_Input(eNum));
	printf("\n%s��%s����̾����ǣ�%dm\n", g->vexs[sNum].name, g->vexs[eNum].name, dist[sNum][eNum]);
	printf("\n�����������·�ߣ�");
	printf("%s->", g->vexs[sNum].name);                                       /*���·���ϵ����*/
	Floyd_Print(g, sNum, eNum);                                               /*���·���ϵ��м��*/
	printf("%s\n\n", g->vexs[eNum].name);                                     /*���·���ϵ��յ�*/
}

/*������ȱ�����ѯ������������֮�������·��*/
int pathStack[M];                                                             /*·��ջ���洢·����Ϣ*/
int top;                                                                      /*ջ��*/
int visited[M];                                                               /*��ջ��ǣ���ֹ�γɻ�·*/
int count;                                                                    /*·��������*/
void Dfs_Print(mgraphtype *g, int sNum, int eNum) {
	int dis = 0,i,j;                                                              /*���ڼ�¼·������*/
	pathStack[top] = sNum;                                                    /*�����������ջ*/
	top++;
	visited[sNum] = 1;                                                        /*����ջ����Ϊ����ջ*/
	for (i = 1; i <= g->vexNum; i++) {
		if (g->edge[sNum][i] > 0 && g->edge[sNum][i] != INFINITY && !visited[i]) {
			/*����ǰһ����ջ����õ�ɴ�Ҹõ�δ��ջ��δ�����ʣ�*/
			if (i == eNum) {                                                  /*�����ȱ����ѵ����յ㣬������ղŵ�·��*/
				printf("��%d��·:", count++);
				for ( j = 0; j < top; j++) 
				{
					printf("%s->", g->vexs[pathStack[j]].name);
					if (j < top - 1)
						dis = dis + g->edge[pathStack[j]][pathStack[j + 1]];        /*ͳ��·������*/
				}
				dis = dis + g->edge[pathStack[top - 1]][eNum];                      /*���һ��·������������Ϊenum������ջ*/
				printf("%s\n", g->vexs[eNum].name);
				printf("�ܳ����ǣ�%dm\n\n", dis);
			}
			else {
				Dfs_Print(g, i, eNum);                                              /*����õ㲻���յ�,�����������*/
				top--;                                                              /*֧·ȫ������һ��󣬶����ջ*/
				visited[i] = 0;                                                     /*����ջ����Ϊ�ѳ�ջ�������´η���*/
			}
		}
	}
}

/*��ѯ������������֮�������·������ӡ*/
void Allpath_Print(mgraphtype *g) {
	int sNum, eNum;
	count = 1;                                                       /*·��������*/
	top = 0;                                                         /*ջ��*/
	memset(pathStack, 0, sizeof(pathStack));                         /*·��ջ��ʼ��*/
	memset(visited, 0, sizeof(visited));                             /*��ջ��ǳ�ʼ��*/
	do {
		printf("\n����������ţ�");
		scanf("%d", &sNum);
	} while (Judge_Input(sNum));
	do {
		printf("\n�������յ��ţ�");
		scanf("%d", &eNum);
	} while (Judge_Input(eNum));
	printf("\n");
	Dfs_Print(g, sNum, eNum);
}

/*�ྰ��������·��*/
void BestPath(mgraphtype *g) {
	int vNum[M] = { 0 }, j = 1;                                       /*��¼�û�����ı����Ϣ*/
	int d = 0,i;                                                        /*ͳ��ȫ���ܳ�*/
	printf("\n��������Ҫ�����ĵ�%d������ı�ţ�����-1�������룩��", j);
	scanf("%d", &vNum[j - 1]);
	while (vNum[j - 1] != -1 && j < 12) 
	{
		while (Judge_Input(vNum[j - 1])) 
		{
			printf("\n��������Ҫ�����ĵ�%d�������ţ�", ++j);
			scanf("%d", &vNum[j - 1]);
		}
		if (vNum[j - 1] == -1) break;
		printf("\n��������Ҫ�����ĵ�%d�������ţ�", ++j);
		scanf("%d", &vNum[j - 1]);
	}
	printf("\n������ѷ���·����");
	for ( i = 0; vNum[i] > 0 && vNum[i + 1] > 0; i++)
	{
		printf("%s->", g->vexs[vNum[i]].name);                   /*���·���ϵ����*/
		Floyd_Print(g, vNum[i], vNum[i + 1]);                /*����Floyd�㷨*/
		d += dist[vNum[i]][vNum[i + 1]];
	}
	printf("%s\n\n", g->vexs[vNum[j - 2]].name);                 /*���·���ϵ��յ�*/
	printf("ȫ���ܳ�Ϊ��%dm\n\n", d);
}

/*���˵�*/
int menu() {
	int s;
	printf("\t\t			 ��ӭʹ��ɽ������ѧԺ������ѯϵͳ \n");
	printf("\t\t    1.ɽ������ѧԺ������Ϣ��ѯ			 2.����������·����ѯ \n");
	printf("\t\t    3.�����������·����ѯ			 4.�ྰ������·�߲�ѯ \n");
	printf("\t\t    5.�˳�У԰������ѯϵͳ \n");
	printf("\t\t������������ѡ�������");
	scanf("%d", &s);
	printf("\n\n");
	return s;
}
/*�ж�����ı���Ƿ����*/
int Judge_Input(int num)
{
	int i = 0;
	if (num == -1)
		return i;
	if (num < 1 || num>13)
	{
		printf("\n����ı������������1-13֮������֣�\n");
		i = 1;
	}

	return i;
}
/*�˳��˵���*/
void System_Exit(int *quit) {
	*quit = 1;
	printf("\t\t                ������������������������������������������                \n");
	printf("\t\t              ������        ��ӭ�´�ʹ�ã�лл��      ������              \n");
	printf("\t\t                ������������������������������������������                \n");
	printf("\t\t                  *     *        *       *         * * *                  \n");
	printf("\t\t                  * *   *        *       *       *       *                \n");
	printf("\t\t                  *  *  *        *       *       *       *                \n");
	printf("\t\t                  *   * *        *       *       *       *                \n");
	printf("\t\t                  *     *          * * *           * * *                  \n");
}

/*������*/
int main() {
	int quit = 0;
	mgraphtype g;
	Create_Map(&g);
	ShortPath(&g);                                                               /*Floyd���dist��path*/
		while (!quit)
		{																		/*ϵͳ�˳����������ж�*/
			switch (menu()) 
			{                                                    /*��ӡ���˵�*/
				case 1:system("cls"); Dis_Map(); Search_Location(&g); break;         /*�б�У԰������Ϣ��ѯ*/
				case 2:system("cls"); Dis_Map(); Shortpath_Print(&g); break;         /*����������·����ѯ*/
				case 3:system("cls"); Dis_Map(); Allpath_Print(&g); break;           /*�����������·����ѯ*/
				case 4:system("cls"); Dis_Map(); BestPath(&g); break;                /*�ྰ������·�߲�ѯ*/
						 /*�������鿴*/
				case 6:system("cls"); System_Exit(&quit); break;                     /*�˳�У԰������ѯϵͳ*/
				default:printf("\t\t\t\t\t����û�и�ѡ���Ӧ�Ĳ�����\n\n");
			}
			system("pause");
			system("cls");                                                           /*����*/
		}
		return 0;
}
