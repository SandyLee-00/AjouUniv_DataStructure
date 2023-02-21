/* - File Name: HW2_4��_201821048.c
 * - Author: seoyeong lee
 * - E-mail Address: syjy8809@gmail.com
 * - Lab Number & Problem Number : HW2_4
 * - Description:

 * - References: �ڷᱸ�� å 10.2, 10.5, 10��, 11��
 * - Last Changed: 12�� 9�� 2019
*/

/*
shortest_path_dijkstra(GraphType *g, int v) :
�׷��� g�� ���� v�κ��� �ٸ� �����鿡 �̸��� �ִ� �Ÿ� ��θ� Diskstra�� �˰����� �̿��Ͽ� ���ϰ�, �� ����� ���. 
����� ����� ����, ���� v�������� �ٸ� vertex������ �̸��� ��ο� �Ÿ��� �����.
*/


/*���� ���ͽ�Ʈ�� �ڵ� ����
��ķ� ǥ���� �� ��ũ�帮��Ʈ�� ��ȭ ����...*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE	1
#define FALSE	0
#define MAX_VERTICES	100		/* ������ �� */
#define INF	100000	/* ���Ѵ� (������ ���� ���) */


typedef struct GraphType {
	int number_of_vertex;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int distance[MAX_VERTICES];/* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES];		/* �湮�� ���� ǥ�� */

int choose(int distance[], int number_of_vertex, int found[])
//���� ���ͽ�Ʈ�� �ڵ�
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < number_of_vertex; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_status(GraphType* g) {
	//���� ���ͽ�Ʈ�� �ڵ�

	static int step = 1;
	printf("STEP %d :", step++);
	printf("\ndistance :");
	for (int i = 0; i < g->number_of_vertex; i++) {
		if (distance[i] == INF) {
			printf(" * ");
		}
		else {
			printf("%3d", distance[i]);
		}
	}
	printf("\n");
	printf("found : ");
	for (int i = 0; i < g->number_of_vertex; i++) {
		printf("%2d", found[i]);
	}
	printf("\n\n");
}

void shortest_path_dijkstra(GraphType* g, int start)
//���� ���ͽ�Ʈ�� �ڵ�
{
	int i, u, w;
	for (i = 0; i < g -> number_of_vertex; i++) /* �ʱ�ȭ */
	{
		distance[i] = g -> weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;    /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;
	for (i = 0; i < g -> number_of_vertex-1; i++) {
		print_status(g);
		u = choose(distance, g -> number_of_vertex, found);
		found[u] = TRUE;
		for (w = 0; w < g -> number_of_vertex; w++)
			if (!found[w])
				if (distance[u] + g -> weight[u][w] < distance[w])
					distance[w] = distance[u] + g -> weight[u][w];
	}
}

int main() {
	//���� ���ͽ�Ʈ�� �ڵ�
	GraphType g = {
		7,{
		{ 0, 7, INF, INF, 3, 10, INF },
		{ 7,  0,    4,  10,   2,   6, INF },
		{ INF,  4,    0,   2, INF, INF, INF },
		{ INF, 10,    2,   0,  11,   9,   4 },
		{ 3,  2,  INF,  11,   0, INF,   5 },
		{ 10,  6,  INF,   9, INF,   0, INF },
		{ INF, INF, INF,   4,   5, INF,   0 } }
	};

	shortest_path_dijkstra(&g, 0);
}