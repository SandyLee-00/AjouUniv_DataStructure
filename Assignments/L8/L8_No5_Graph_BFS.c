/* - File Name: L8_No5_Graph_BFS.c
 * - Author: seoyeong lee
 * - E-mail Address: syjy8809@gmail.com
 * - Lab Number & Problem Number : L8_No5
 * - Description: ���α׷� ������ ������ ������
 * - References: �ڷᱸ�� å 10.2, 10.5
 * - Last Changed: nov 14, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode //å 10.2
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType { //å 10.2
	int number_of_vertex;	// ������ ����
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g) //å 10.2
{
	int v;
	g->number_of_vertex = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v) //å 10.2
{
	if (((g->number_of_vertex) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->number_of_vertex++;
}
// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType* g, int fir, int sec) //å 10.2
{
	GraphNode* node;
	if (fir >= g->number_of_vertex || sec >= g->number_of_vertex) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = sec;
	node->link = g->adj_list[fir];
	g->adj_list[fir] = node;
}

void print_adf_list(GraphType* g) { //å 10.2 ����
	for (int i = 0; i < g->number_of_vertex; i++) {
		GraphNode* p = g->adj_list[i];
		printf("���� %d�� ����Ʈ", i);
		if (p == NULL) { 
			//�̰��� �߰����� ������ ���� �� �����
			printf("  NULL");
		}
		else {
			while (p != NULL)
				//ó���� p�� ��ũ�� ���� �������� �ߴٰ�
				//���� �ڵ尡 �¾Ҵ�. �������� ���̸� ��� ���ϱ� �����̴�.
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


void bfs_list(GraphType* g, int v) //å 10.5
{
	GraphNode* w;
	QueueType q;
	init(&q);    				// ť �ʱ� ȭ 
	visited[v] = TRUE;      // ���� sec �湮 ǥ�� 
	printf("%d ", v);          // �湮�� ���� ��� 
	enqueue(&q, v);			// ���������� ť�� ���� 
	while (!is_empty(&q)) {
		v = dequeue(&q);		// ť�� ����� ���� ���� 
		for (w = g->adj_list[v]; w; w = w->link) //���� ���� Ž��
			if (!visited[w->vertex]) {	// �̹湮 ���� Ž�� 
				visited[w->vertex] = TRUE;   // �湮 ǥ��
				printf("%d ", w->vertex);
				enqueue(&q, w->vertex);	//������ ť�� ����
			}
	}
}

int main(void) //å 10.5
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
	//���� �ڵ尡 �߸��Ǿ ������ �ð��� �ɷȴ�.
	printf("�ʺ� �켱 Ž��\n");
	bfs_list(g, 0);
	printf("\n");
	
	free(g);
	return 0;
}