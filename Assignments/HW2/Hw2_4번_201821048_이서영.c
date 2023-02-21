/* - File Name: HW2_4번_201821048.c
 * - Author: seoyeong lee
 * - E-mail Address: syjy8809@gmail.com
 * - Lab Number & Problem Number : HW2_4
 * - Description:

 * - References: 자료구조 책 10.2, 10.5, 10장, 11장
 * - Last Changed: 12월 9일 2019
*/

/*
shortest_path_dijkstra(GraphType *g, int v) :
그래프 g의 정점 v로부터 다른 정점들에 이르는 최단 거리 경로를 Diskstra의 알고리즘을 이용하여 구하고, 그 결과를 출력. 
결과를 출력할 때는, 정점 v에서부터 다른 vertex까지에 이르는 경로와 거리를 출력함.
*/


/*교재 다익스트라 코드 참고
행렬로 표현된 것 링크드리스트로 변화 못함...*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE	1
#define FALSE	0
#define MAX_VERTICES	100		/* 정점의 수 */
#define INF	100000	/* 무한대 (연결이 없는 경우) */


typedef struct GraphType {
	int number_of_vertex;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];		/* 방문한 정점 표시 */

int choose(int distance[], int number_of_vertex, int found[])
//교재 다익스트라 코드
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
	//교재 다익스트라 코드

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
//교재 다익스트라 코드
{
	int i, u, w;
	for (i = 0; i < g -> number_of_vertex; i++) /* 초기화 */
	{
		distance[i] = g -> weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;    /* 시작 정점 방문 표시 */
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
	//교재 다익스트라 코드
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