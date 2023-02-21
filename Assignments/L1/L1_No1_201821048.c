/* Program 5.5 in p.169 C���� ���� Ǯ� �ڷᱸ��, ����3��, õ�α� �� ��, �������ǻ� */

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

#define MAX_SIZE = 10; //9����� ��Ⱑ��

 // ���α׷� 5.2���� ������ ���� �κ��� �����Ѵ�.
 // ================ ����ť �ڵ� ���� =================
typedef struct { // ��� Ÿ�� //�������� �ֽ� �κ�
	10 int id;
	11 int arrival_time;
	12 int service_time;
	13
} element; // ��ü!



typedef struct { //���� ť�� �迭�� ������, 5����� �պκ� front ������ rear�� ������
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void init_queue(QueueType* q);
int is_empty(QueueType* q);
int is_full(QueueType* q);
void enqueue(QueueType* q, element item);
element dequeue(QueueType* q);
element peek(QueueType* q);
void queue_print(QueueType* q);
int get_count(QueueType* q);

void init_queue(QueueType* q) //�հ� �ڸ� 0���� �ʱ⼳����//�������� ���� 3���� �ֽ�
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q) //������� Ȯ��, �հ� �ڰ� ������ ������� 1, �ƴ� 0//�������� ���� 3���� �ֽ�
{
	return (q->front == q->rear);
}

int is_full(QueueType* q) //á���� Ȯ��, �հ� ((�� + 1)�� ��ⷯ �� ��)�� ������ ��밡���� ĭ ���� á��//�������� ���� 3���� �ֽ�
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
int get_count(QueueType* q) { //�� - ��, ���� �� ĭ�� ����Ű�� ����//���� 3���� ���

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


// ================ ����ť �ڵ� ���� =================


int main(void) //�������� �ֽ� �κ�
{
	int minutes = 60;
	int total_wait = 0;
	int total_customers = 0;
	int service_time = 0;
	int service_customer;
	QueueType queue;
	init_queue(&queue);
	srand(time(NULL));

	for (int clock = 0; clock < minutes; clock++) {
		printf("����ð�=%d\n", clock);
		if ((rand() % 10) < 3) {
			element customer;
			customer.id = total_customers++;
			customer.arrival_time = clock;
			customer.service_time = rand() % 3 + 1;
			enqueue(&queue, customer);
			printf("�� %d�� %d�п� ���ɴϴ�. ����ó���ð�= %d��\n",
				customer.id, customer.arrival_time, customer.service_time);

		}
		if (service_time > 0) {
			printf("�� %d ����ó�����Դϴ�. \n", service_customer);
			service_time--;

		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				printf("�� %d�� %d�п� ������ �����մϴ�. ���ð��� %d���̾����ϴ�.\n",
					customer.id, clock, clock - customer.arrival_time);
				total_wait += clock - customer.arrival_time;

			}

		}

	}
	printf("��ü ��� �ð�=%d�� \n", total_wait);
	return 0;
}