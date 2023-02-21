#define _CRT_SECURE_NO_WARNINGS
/* Program 5.2 in p.157 C���� ���� Ǯ� �ڷᱸ��, ����3��, õ�α� �� ��, �������ǻ�
*/
/*
File Name : L2_No3_201821048_201821048.c
Author : Lee Seoyeong
Email : syjy8809@gmail.com
Lab Number & Problem Number : L2_No3
Description : ����ť�� ����ϴ� ���α׷����� ������ ����ϴ� ��� �߰��ϱ�
References : Program 5.2 in p.157 C���� ���� Ǯ� �ڷᱸ��, ����3��, õ�α� �� ��, �������ǻ�
Last Changed: September 25, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5 //���� ť ��ü ������ 5, ��밡�� 4ĭ

typedef int element; //int ���� ������ ����

typedef struct { //���� ť�� �迭�� ������, 5����� �պκ� front ������ rear�� ������
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(char* message);
void init_queue(QueueType* q);
int is_empty(QueueType* q);
int is_full(QueueType* q);
void enqueue(QueueType* q, element item);
element dequeue(QueueType* q);
element peek(QueueType* q);
void queue_print(QueueType* q);
int get_count(QueueType* q);

// �����Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// �ʱ�ȭ �Լ�
void init_queue(QueueType* q) //�հ� �ڸ� 0���� �ʱ⼳����
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q) //������� Ȯ��, �հ� �ڰ� ������ ������� 1, �ƴ� 0
{
	return (q->front == q->rear);
}

int is_full(QueueType* q) //á���� Ȯ��, �հ� ((�� + 1)�� ��ⷯ �� ��)�� ������ ��밡���� ĭ ���� á��
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int get_count(QueueType* q) { //�� - ��, ���� �� ĭ�� ����Ű�� ����

	int count = (q->rear % MAX_QUEUE_SIZE) - (q->front % MAX_QUEUE_SIZE);
	if (count < 0) { //�ѹ����� ���� rear�� ���ڰ� front ���� �۾����� -�� �ȴ�. �׷��� �׸�ŭ ��������ϱ� ��ü - ��ĭ�� �ؼ� �� ĭ�� ����.
		count = MAX_QUEUE_SIZE - count;
	}
	return count;
}

void queue_print(QueueType* q) //ť �������
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear); //front�� rear ��ġ ���
	if (!is_empty(q)) { //������� ������
		int i = q->front; //i�� front ����
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE); //front + 1�ؼ� �� ĭ���� �̵� �� ��ⷯ ����
			printf("%d|", q->data[i]); //���� ĭ ������ ���
			if (i == q->rear) //rear���� ����ϸ� ������
				break;

		} while (i != q->front); //�� ĭ�� front�̸� �ȵȴ�.(�� ���� break�� ����������.)

	}
	printf("\n"); //����

	printf("%d\n", get_count(q)); //getcount�� ����ť�� ����ִ� �͵� ������ش�.
}

// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	//���� �˰���
	if (is_full(q))
		error(" ť�� ��ȭ�����Դϴ�\n"); //á���� ��ȭ�޽��� ���
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; //rear ��ĭ�ڷΰ��� (��ⷯ)
	q->data[q->rear] = item; //�� ĭ�� ���ο� ������ �ֱ�
}

// ���� �Լ�
element dequeue(QueueType* q)
{
	//���� �˰���
	if (is_empty(q)) //������� ����޽��� ���
		error(" ť�� ��������Դϴ�\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; //front ť�� �� ĭ���� �̵� (��ⷯ);
	return q->data[q->front]; //���� ĭ�� �� ��ȯ
}

// peek �Լ�
element peek(QueueType* q) //�� ����
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�"); //������ ����
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE]; //�տ� ��ĭ ������ ��ȯ

}

int main() //�������� �÷��ֽ� �ڵ�
{
	QueueType q; //q�� ����
	int element; //������ �Է¿�

	init_queue(&q); //q 
	printf("--������ �߰� �ܰ�--\n");
	while (!is_full(&q))
	{
		printf("������ �Է��Ͻÿ�: ");
		scanf_s("%d", &element);
		enqueue(&q, element);
		queue_print(&q);
	}
	printf("ť ��ȭ����\n\n");

	printf("--������ ���� �ܰ�--\n");
	while (!is_empty(&q))
	{
		element = dequeue(&q);
		printf("������ ����: %d \n", element);
		queue_print(&q);
	}
	printf("ť�� �������\n");
	return 0;
}