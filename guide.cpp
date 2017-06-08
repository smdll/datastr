#include<stdio.h>
#include<string.h>
#define INF 100

char Edge[10][10] = {
{0,   5,   INF, 5,   5,   INF, INF, INF, INF, INF},
{5,   0,   2,   INF, INF, INF, INF, INF, INF, INF},
{INF, 2,   0,   5,   INF, INF, INF, 4,   3,   INF},
{5,   INF, 5,   0,   5,   4,   INF, INF, INF, INF},
{5,   INF, INF, 5,   0,   INF, INF, INF, INF, INF},
{INF, INF, INF, 4,   INF, 0,   8,   10,  INF, INF},
{INF, INF, INF, INF, INF, 8,   0,   INF, INF, INF},
{INF, INF, 4,   INF, INF, 10,  INF, 0,   3,   4},
{INF, INF, 3,   INF, INF, INF, INF, 3,   0,   INF},
{INF, INF, INF, INF, INF, INF, INF, 4,   INF, 0}};

char dist[10][10];
char path[10][10];

struct Edgetype
{
	char name[15];
	char info[30];
} map[10];

void init()
{
	strcpy(map[0].name, "南门"); strcpy(map[0].info, "广西大学主进出口");
	strcpy(map[1].name, "狗洞"); strcpy(map[1].info, "南校园的商业街");
	strcpy(map[2].name, "图书馆"); strcpy(map[2].info, "广西大学图书馆");
	strcpy(map[3].name, "西体育馆"); strcpy(map[3].info, "西校园体育馆");
	strcpy(map[4].name, "西门"); strcpy(map[4].info, "西校园进出口");
	strcpy(map[5].name, "农场"); strcpy(map[5].info, "农类生产实验基地");
	strcpy(map[6].name, "行健学院"); strcpy(map[6].info, "广西大学行健学院");
	strcpy(map[7].name, "东水塔"); strcpy(map[7].info, "东校园地标");
	strcpy(map[8].name, "校医院"); strcpy(map[8].info, "广西大学校医院");
	strcpy(map[9].name, "东门"); strcpy(map[9].info, "东校园进出口");
}

void floyd()
{
	int i, j, k;
	for(i = 0; i < 10 ; i++)
	{
		for(j = 0; j < 10; j++)
		{
			dist[i][j] = Edge[i][j];
			if(Edge[i][j] == INF)
				path[i][j] = -1;//表示  i -> j 不通 
			else
				path[i][j] = i;// 表示 i -> j 前驱为 i
		}
	}
	for(k = 0; k < 10; k++)
	{
		for(i = 0; i < 10; i++)
		{
			for(j = 0; j < 10; j++)
			{
				if(!(dist[i][k] == INF || dist[k][j] == INF) && dist[i][j] > dist[i][k] + dist[k][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}
}

void printMap()
{
	printf("编号\t地名\n");
	for(int i = 0; i < 10; i++)
		printf("%d\t%s\n", i + 1, map[i].name);
}

void printNode(int from)
{
	printf("\n地名\t简介\n");
	printf("%s\t%s\n", map[from].name, map[from].info);
}

void printPath(int i, int j) {
	int apath[10], k, d;
	printf("\n从 %s 到 %s 的路径:", map[i].name, map[j].name);
	k = path[i][j];
	d = 0;
	apath[d] = j;
	while(k != -1 && k != i)
	{
		d++;
		apath[d] = k;
		k = path[i][k];
	}
	d++;
	apath[d] = i;
	printf("%s", map[apath[d]].name);
	for(int s = d - 1; s >= 0; s--)
		printf(" -> %s", map[apath[s]].name);
	printf("\n路径长度: %d00 米\n", dist[i][j]);
}

int main()
{
	char select;
	int from, to;
	init();
	floyd();
	printMap();
	do
	{
		printf("\n0:退出\t1:显示所有地点\t2:显示地点介绍\t3:显示两景点之间最短路径\n");
		printf("操作:");
		scanf("%c", &select);
		getchar();
		switch(select)
		{
			case '1':
				printMap();
				break;
			case '2':
				printf("\n输入景点编号:");
				scanf("%d", &from);
				getchar();
				from--; 
				if(from < 0 || from > 9)
				{
					printf("\n景点不存在！\n");
					break;
				}
				printNode(from);
				break;
			case '3':
				printf("\n从:到");
				scanf("%d:%d", &from, &to);
				getchar();
				from--;
				to--;
				if(from < 0 || from > 9 || to < 0 || to > 9)
				{
					printf("\n景点不存在！\n");
					break;
				}
				printPath(from, to);
				break;
		}
	}while(select != '0');
	return 0;
}
