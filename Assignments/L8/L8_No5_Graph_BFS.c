/* - File Name: L8_No5_Graph_BFS.c
 * - Author: seoyeong lee
 * - E-mail Address: syjy8809@gmail.com
 * - Lab Number & Problem Number : L8_No5
 * - Description: 프로그램 설명을 간단히 쓰세요
 * - References: 자료구조 책 10.2, 10.5
 * - Last Changed: nov 14, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode //책 10.2
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType { //책 10.2
	int number_of_vertex;	// 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g) //책 10.2
{
	int v;
	g->number_of_vertex = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) //책 10.2
{
	if (((g->number_of_vertex) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->number_of_vertex++;
}
// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType* g, int fir, int sec) //책 10.2
{
	GraphNode* node;
	if (fir >= g->number_of_vertex || sec >= g->number_of_vertex) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = sec;
	node->link = g->adj_list[fir];
	g->adj_list[fir] = node;
}

void print_adf_list(GraphType* g) { //책 10.2 변형
	for (int i = 0; i < g->number_of_vertex; i++) {
		GraphNode* p = g->adj_list[i];
		printf("정점 %d의 리스트", i);
		if (p == NULL) { 
			//이것을 추가하지 않으면 널일 때 멈춘다
			printf("  NULL");
		}
		else {
			while (p != NULL)
				//처음에 p의 링크가 널일 때까지로 했다가
				//원래 코드가 맞았다. 다음것이 널이면 출력 안하기 떄문이다.
			{
				printf("-> %d", p->vertex);
				p = p->link;
			}
		}
		printf("\n");
	}
}

int visited[MAX_VERTICES];

#define MAX_QUEUE_SIZE 100


void bfs_list(GraphType* g, int v) //책 10.5
{
	GraphNode* w;
	QueueType q;
	init(&q);    				// 큐 초기 화 
	visited[v] = TRUE;      // 정점 sec 방문 표시 
	printf("%d ", v);          // 방문한 정점 출력 
	enqueue(&q, v);			// 시작정점을 큐에 저장 
	while (!is_empty(&q)) {
		v = dequeue(&q);		// 큐에 저장된 정점 선택 
		for (w = g->adj_list[v]; w; w = w->link) //인접 정점 탐색
			if (!visited[w->vertex]) {	// 미방문 정점 탐색 
				visited[w->vertex] = TRUE;   // 방문 표시
				printf("%d ", w->vertex);
				enqueue(&q, w->vertex);	//정점을 큐에 삽입
			}
	}
}

int main(void) //책 10.5
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);
	for (int i = 0; i < 6; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 0, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 1, 5);
	print_adf_list(g); 
	//원래 코드가 잘못되어서 수정에 시간이 걸렸다.
	printf("너비 우선 탐색\n");
	bfs_list(g, 0);
	printf("\n");
	
	free(g);
	return 0;
}