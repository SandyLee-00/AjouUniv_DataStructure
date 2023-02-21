
/* 1.
   - File Name: L1_2Maze.c
 * - Author: Seoyong Lee
 * - E-mail Address: syjy8809@gmail.com 
 * - Lab Number & Problem Number : L1_No2 
 * - Description: 미로탐색 프로그램 미로변경 후 탐색 실행하기, 미로출력과 스택출력
 * - References: code5-8c.c
 * - Last Changed: September 20, 2019

  2. 
  Sorce File List for L1_No2 :
  L1_2Maze.c

  3.
  윈도우, 비주얼스튜디오 2019

  4.
  사용함.
  스택 구현부분 : code5-3.c //자료구조 책 코드
  미로제작방식 : code5-8c.c
  스택출력, 미로출력  : 교수님 코드
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 4
#define MAZE_SIZE 6

typedef struct {	//row와 colum을 element로 묶음, code5-8c.c
	short r;
	short c;
} element;

typedef struct {
	element data[MAX_STACK_SIZE];	//스택으로 각 좌표의 위치를 구현하도록 함
	int top;						//element형태로 가로, 세로가 이용될 수 있게 데이터란 이름으로 맥스사이즈4만큼 선언
} StackType;						//top은 가장 위 표현

element here = { 1, 0 }, entry = { 1, 0 };	//처음 좌표가 1,0에서 시작함, code5-8c.c

char maze[MAZE_SIZE][MAZE_SIZE] = {		//프린트에 있는 실습4그림대로 미로를 그림
{ '1', '1', '1', '1', '1', '1' },
{ 'e', '0', '0', '0', '1', '1' },
{ '1', '1', '0', '1', '1', '1' },
{ '1', '1', '0', '1', '1', '1' },
{ '1', '0', '0', '0', '0', 'x' },
{ '1', '1', '1', '1', '1', '1' },
};

void initialize(StackType* s)	//스택시작, code5-8c.c
{
	s->top = -1;
}

int isEmpty(StackType* s)	//비었는지 확인, code5-8c.c
{
	return (s->top == -1);
}

int isFull(StackType* s)	//찼는지 확인, code5-8c.c
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)	//삽입, 찼는지 확인하기, 아니면 넣기, code5-8c.c
{
	if (isFull(s)) {
		printf("stack is full\n");
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s)	//빼기, 비었는지 확인, 아니면 넣기, code5-8c.c
{
	if (isEmpty(s)) {
		printf("stack is empty\n");
	}
	else return s->data[(s->top)--];
}

void pushLoc(StackType* s, int r, int c)	//벽과 지나간길아니면 받은값 push해주기
{
	if (r < 0 || c < 0) return 0;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])	//교수님코드
{
	int r, c;
	printf("\n");
	for (r = 0; r < MAZE_SIZE; r++) {
		for (c = 0; c < MAZE_SIZE; c++) {
			if (c == here.c && r == here.r)
				printf("m");
			else {
				//if (m[r][c] == 0) printf("0");
				//else printf("%c", m[r][c]);
				printf("%c", maze[r][c]);
			}
		}
		printf("\n");
	}
	printf("\n\n");
}
void print_stack(StackType* s)	//교수님코드
{
	int i;
	for (i = 5; i > s->top; i--)
		printf("|     |\n");
	for (i = s->top; i >= 0; i--)
		printf("|(%01d,%01d)|\n", s->data[i].r, s->data[i].c);
	printf("-------\n");
}


/* 스택 push, pop 연산 뒤에서 미로와 스택을 아래 코드처럼 출력 //교수님코드
   maze_print(maze);
   print_stack(&s);
*/

int main()	//메인에서 실행하기, code5-8c.c
{
	int r, c;
	StackType s;	//s만들기
	init_stack(&s);	//s실행
	maze_print(maze);	//처음미로출력
	
	while (maze[here.r][here.c] != 'x') {	//도착점에 갈때까지

		printf("구별선=============");
		r = here.r;
		c = here.c;
		maze[r][c] = '.';	//간 곳
		maze_print(maze);	//push전 미로출력
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);
		print_stack(&s);	//push 후 스택출력
		if (isEmpty(&s)) {	//가능한 남아있는 갈림길이 없으면 다 갔음
			printf("실패\n");
			return 0;
		}
		else
			here = pop(&s);	//스택에서 빼기
			print_stack(&s);	//pop 후 스택출력
	}
	printf("성공\n");	//와일루프를 도착점에 도착해 빠져나감

	return 0;
}