
/* - File Name: HW2_1_2_3_201821048.c
 * - Author: seoyeong lee
 * - E-mail Address: syjy8809@gmail.com
 * - Lab Number & Problem Number : HW2_1_2_3
 * - Description:
 1. 링크드리스트로 텍스트에서 가져온 그래프를 구현함
 2. 그래프를 출력해 링크드리스트 모양으로 나오도록 함
 3. 깊이우선탐색을 구현함

 * - References: 자료구조 책 10.2, 10.5, 10장, 11장
 * - Last Changed: 12월 9일 2019
*/
#define _CRT_SECURE_NO_WARNINGS   
#pragma warning(disable : 4996)

#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0
#define INF 10000

#include <stdio.h>
#include <stdlib.h>

typedef struct GraphNode //책 10.2
{
	int vertex;
	int weight;
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
void insert_edge(GraphType* g, int fir, int sec, char weight) //책 10.2
{
	GraphNode* node;
	if (fir >= g->number_of_vertex || sec >= g->number_of_vertex) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = sec;
	node->weight = weight;
	node->link = g->adj_list[fir];
	g->adj_list[fir] = node;
}
/*print_graph_list (GraphType *g) :
인접리스트 형태의 그래프 g의 정보를 화면에 출력
(인접리스트 형태를 알아 볼 수 있도록 할 것)*/

void print_graph_list(GraphType* g) { //책 10.2 변형
	for (int i = 0; i < g->number_of_vertex; i++) {
		GraphNode* p = g->adj_list[i];
		printf("정점 %d의 리스트", i);
		if (p == NULL) {
			//이것을 추가하지 않으면 널일 때 멈춘다
			printf("-> NULL");
		}
		else {
			while (p != NULL)
				//처음에 p의 링크가 널일 때까지로 했다가
				//원래 코드가 맞았다. 다음것이 널이면 출력 안하기 문이다.
			{
				printf("-> %d", p->vertex);
				p = p->link;
			}
		}
		printf("\n");
	}
}

/*read_graph_mat (GraphType *g, char *name) :
이름이 name인 그래프 텍스트 파일(예: “graph1.txt”)을 읽어서
인접리스트 형태의 그래프 g에 저장*/
//1. 엣지의 무게가 17이상이면 inf로 처리된다
//2. 텍스트파일의 이름을 받아서 파일을 열 수 없다.

void read_graph_mat(GraphType* g, char* name) {
	printf("%s의 ", name);
	int buffer[20][20] = { 0 };

	FILE* fp = fopen(name, "r");
	//그래프 2 파일의 데이터 읽기

	fscanf(fp, "%d", &buffer[0][0]);
	//첫번째에 나오는 값 == 총 버텍스 개수 받기

	int numofvertex = buffer[0][0];
	//버택스 개수 저장
	printf("vertex의 개수 : %d\n", numofvertex);

	for (int i = 1; i < numofvertex + 1; i++) {
		for (int j = 0; j < numofvertex; j++) {
			//나머지 데이터를 버텍스 개수에 맞게 입력을 받음
			fscanf(fp, "%d", &buffer[i][j]);
			if (buffer[i][j] > 100) {
				//100초과이면 무한으로 처리
				printf("%d에서 %d로의 엣지의 무게 INF\n", i - 1, j);
			}
			else {
				//그 외 다른 모든 버텍스와 연결되는 엣지를 입력한다.
				printf("%d에서 %d로의 엣지의 무게 %d\n", i - 1, j, buffer[i][j]);
			}
		}printf("\n");
	}

	for (int i = 0; i < numofvertex; i++)
		insert_vertex(g, i); //정점 추가

	for (int i = 0; i < numofvertex; i++) {
		for (int j = 0; j < numofvertex; j++) {
			//배열을 리스트 형태로 바꾸기 위해 엣지를 넣는다.
			if (i == j || buffer[i + 1][j] > 100) {
				//자신 or 무한의 거리인 버텍스와는 엣지 연결 안함
			}
			else {
				//그 외 버텍스와 연결함, 무게도 넣어줌
				insert_edge(g, i, j, buffer[i + 1][j]);
			}
		}
	}

	fclose(fp);
}
/*dfs (GraphType *g, int v) :
그래프 g의 정점 v를 시작으로 하여
깊이 우선 탐색 (depth first search) 순서를 화면에 출력.
정점 이름만 순서대로 출력할 것.*/
int visited[MAX_VERTICES];

//전역변수로 설정해놔서 초기화 해줘야함
void set_null() {
	for (int i = 0; i < MAX_VERTICES; i++) {
		visited[i] = 0;
	}
}


void dfs_list(GraphType* g, int v)
//책 프로그램 10.4
{
	GraphNode* w;
	visited[v] = TRUE;   		// 정점 v의 방문 표시 
	printf("%d ", v);   		// 방문한 정점 출력 
	for (w = g->adj_list[v]; w; w = w->link)// 인접 정점 탐색 
	{
		if (!visited[w->vertex]) {
			dfs_list(g, w->vertex); //정점 w에서 DFS 새로시작
		}
	}
}


int main()
{
	GraphType* graph1;
	char graph1_[40] = "graph1.txt";
	graph1 = (GraphType*)malloc(sizeof(GraphType));
	graph_init(graph1);
	read_graph_mat(graph1, graph1_);

	print_graph_list(graph1);

	printf("깊이 우선 탐색\n");
	set_null();
	dfs_list(graph1, 0);
	printf("\n");
	free(graph1);

	GraphType* graph2;
	char graph2_[40] = "graph2.txt";
	graph2 = (GraphType*)malloc(sizeof(GraphType));
	graph_init(graph2);
	read_graph_mat(graph2, graph2_);

	print_graph_list(graph2);

	printf("깊이 우선 탐색\n");
	set_null();
	dfs_list(graph2, 0);
	printf("\n");
	free(graph2);

	return 0;
}