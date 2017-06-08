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
	strcpy(map[0].name, "����"); strcpy(map[0].info, "������ѧ��������");
	strcpy(map[1].name, "����"); strcpy(map[1].info, "��У԰����ҵ��");
	strcpy(map[2].name, "ͼ���"); strcpy(map[2].info, "������ѧͼ���");
	strcpy(map[3].name, "��������"); strcpy(map[3].info, "��У԰������");
	strcpy(map[4].name, "����"); strcpy(map[4].info, "��У԰������");
	strcpy(map[5].name, "ũ��"); strcpy(map[5].info, "ũ������ʵ�����");
	strcpy(map[6].name, "�н�ѧԺ"); strcpy(map[6].info, "������ѧ�н�ѧԺ");
	strcpy(map[7].name, "��ˮ��"); strcpy(map[7].info, "��У԰�ر�");
	strcpy(map[8].name, "УҽԺ"); strcpy(map[8].info, "������ѧУҽԺ");
	strcpy(map[9].name, "����"); strcpy(map[9].info, "��У԰������");
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
				path[i][j] = -1;//��ʾ  i -> j ��ͨ 
			else
				path[i][j] = i;// ��ʾ i -> j ǰ��Ϊ i
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
	printf("���\t����\n");
	for(int i = 0; i < 10; i++)
		printf("%d\t%s\n", i + 1, map[i].name);
}

void printNode(int from)
{
	printf("\n����\t���\n");
	printf("%s\t%s\n", map[from].name, map[from].info);
}

void printPath(int i, int j) {
	int apath[10], k, d;
	printf("\n�� %s �� %s ��·��:", map[i].name, map[j].name);
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
	printf("\n·������: %d00 ��\n", dist[i][j]);
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
		printf("\n0:�˳�\t1:��ʾ���еص�\t2:��ʾ�ص����\t3:��ʾ������֮�����·��\n");
		printf("����:");
		scanf("%c", &select);
		getchar();
		switch(select)
		{
			case '1':
				printMap();
				break;
			case '2':
				printf("\n���뾰����:");
				scanf("%d", &from);
				getchar();
				from--; 
				if(from < 0 || from > 9)
				{
					printf("\n���㲻���ڣ�\n");
					break;
				}
				printNode(from);
				break;
			case '3':
				printf("\n��:��");
				scanf("%d:%d", &from, &to);
				getchar();
				from--;
				to--;
				if(from < 0 || from > 9 || to < 0 || to > 9)
				{
					printf("\n���㲻���ڣ�\n");
					break;
				}
				printPath(from, to);
				break;
		}
	}while(select != '0');
	return 0;
}
