
/* 1.
   - File Name: L1_2Maze.c
 * - Author: Seoyong Lee
 * - E-mail Address: syjy8809@gmail.com 
 * - Lab Number & Problem Number : L1_No2 
 * - Description: �̷�Ž�� ���α׷� �̷κ��� �� Ž�� �����ϱ�, �̷���°� �������
 * - References: code5-8c.c
 * - Last Changed: September 20, 2019

  2. 
  Sorce File List for L1_No2 :
  L1_2Maze.c

  3.
  ������, ���־�Ʃ��� 2019

  4.
  �����.
  ���� �����κ� : code5-3.c //�ڷᱸ�� å �ڵ�
  �̷����۹�� : code5-8c.c
  �������, �̷����  : ������ �ڵ�
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 4
#define MAZE_SIZE 6

typedef struct {	//row�� colum�� element�� ����, code5-8c.c
	short r;
	short c;
} element;

typedef struct {
	element data[MAX_STACK_SIZE];	//�������� �� ��ǥ�� ��ġ�� �����ϵ��� ��
	int top;						//element���·� ����, ���ΰ� �̿�� �� �ְ� �����Ͷ� �̸����� �ƽ�������4��ŭ ����
} StackType;						//top�� ���� �� ǥ��

element here = { 1, 0 }, entry = { 1, 0 };	//ó�� ��ǥ�� 1,0���� ������, code5-8c.c

char maze[MAZE_SIZE][MAZE_SIZE] = {		//����Ʈ�� �ִ� �ǽ�4�׸���� �̷θ� �׸�
{ '1', '1', '1', '1', '1', '1' },
{ 'e', '0', '0', '0', '1', '1' },
{ '1', '1', '0', '1', '1', '1' },
{ '1', '1', '0', '1', '1', '1' },
{ '1', '0', '0', '0', '0', 'x' },
{ '1', '1', '1', '1', '1', '1' },
};

void initialize(StackType* s)	//���ý���, code5-8c.c
{
	s->top = -1;
}

int isEmpty(StackType* s)	//������� Ȯ��, code5-8c.c
{
	return (s->top == -1);
}

int isFull(StackType* s)	//á���� Ȯ��, code5-8c.c
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)	//����, á���� Ȯ���ϱ�, �ƴϸ� �ֱ�, code5-8c.c
{
	if (isFull(s)) {
		printf("stack is full\n");
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s)	//����, ������� Ȯ��, �ƴϸ� �ֱ�, code5-8c.c
{
	if (isEmpty(s)) {
		printf("stack is empty\n");
	}
	else return s->data[(s->top)--];
}

void pushLoc(StackType* s, int r, int c)	//���� ��������ƴϸ� ������ push���ֱ�
{
	if (r < 0 || c < 0) return 0;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])	//�������ڵ�
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
void print_stack(StackType* s)	//�������ڵ�
{
	int i;
	for (i = 5; i > s->top; i--)
		printf("|     |\n");
	for (i = s->top; i >= 0; i--)
		printf("|(%01d,%01d)|\n", s->data[i].r, s->data[i].c);
	printf("-------\n");
}


/* ���� push, pop ���� �ڿ��� �̷ο� ������ �Ʒ� �ڵ�ó�� ��� //�������ڵ�
   maze_print(maze);
   print_stack(&s);
*/

int main()	//���ο��� �����ϱ�, code5-8c.c
{
	int r, c;
	StackType s;	//s�����
	init_stack(&s);	//s����
	maze_print(maze);	//ó���̷����
	
	while (maze[here.r][here.c] != 'x') {	//�������� ��������

		printf("������=============");
		r = here.r;
		c = here.c;
		maze[r][c] = '.';	//�� ��
		maze_print(maze);	//push�� �̷����
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);
		print_stack(&s);	//push �� �������
		if (isEmpty(&s)) {	//������ �����ִ� �������� ������ �� ����
			printf("����\n");
			return 0;
		}
		else
			here = pop(&s);	//���ÿ��� ����
			print_stack(&s);	//pop �� �������
	}
	printf("����\n");	//���Ϸ����� �������� ������ ��������

	return 0;
}