/*  */
/*
File Name : L2_No4_201821048.c
Lee Seoyeong
L2_No4
���� 2���� ����ũ���� ť���� ��ٸ��� ������� �̾� ���� ���� ó���Ѵ�.
Program 5.5 in p.169 C���� ���� Ǯ� �ڷᱸ��, ����3��, õ�α� �� ��, �������ǻ�
September 29, 2019
*/

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <stdbool.h>

#define MAX_QUEUE_SIZE 10 //9����� ��Ⱑ��
#define minutes 30 //����ð�


 // ���α׷� 5.2���� ������ ���� �κ��� �����Ѵ�.
 // ================ ����ť �ڵ� ���� =================
typedef struct { // ��� Ÿ�� //�������� �ֽ� �κ�
	 int id;
	 int arrival_time;
	 int service_time;
} client; 

typedef struct { //���� ť�� �迭�� ������, 5����� �պκ� front ������ rear�� ������
	client data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

typedef struct { //������� �� ����ũ���� ó���ϵ��� Server_able Ÿ���� �������.
	bool empty; //ó���ϴ� ����ũ�� ������� Ȯ�ο� ������� 1, ó�����̸� 0
	int service_time; //ó���ϴ� �մ��� �ʿ伭�� �ð�����
	int service_customer; //ó���ϴ� �մ��� ���̵� ����
}Server_able;
/*�� ���� ť �����κ��� �������� �ֽ� L2_No3�������� �����
*/

void init_queue(QueueType* q);
int is_empty(QueueType* q);
int is_full(QueueType* q);
void enqueue(QueueType* q, client item);
client dequeue(QueueType* q);
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


// ���� �Լ�
void enqueue(QueueType* q, client item)
{
	//���� �˰���
	if (is_full(q))
		printf(" ť�� ��ȭ�����Դϴ�\n"); //á���� ��ȭ�޽��� ���
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; //rear ��ĭ�ڷΰ��� (��ⷯ)
	q->data[q->rear] = item; //�� ĭ�� ���ο� ������ �ֱ�
}

// ���� �Լ�
client dequeue(QueueType* q)
{
	//���� �˰���
	if (is_empty(q)) //������� ����޽��� ���
		printf(" ť�� ��������Դϴ�\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; //front ť�� �� ĭ���� �̵� (��ⷯ);
	return q->data[q->front]; //���� ĭ�� �� ��ȯ
}




// ================ ����ť �ڵ� ���� =================


int main(void) //�������� �ֽ� �κ�
{
	int total_wait = 0; //��ü �մ� ���ð� ī��Ʈ
	int total_customers = 0; //��ü �湮 �մ� �� ī��Ʈ
	int total_finished_customers = 0; ////��ü ó���� �մ� �� ī��Ʈ, �ð��� �Ǿ� �Ұ����ϸ� ���� �ʴ´�.

	QueueType queue; //��� ��� ť ����
	Server_able oneserv; //ó�� ��� ����ũ 1 ����
	Server_able twoserv; //ó�� ��� ����ũ 2 ����

	oneserv.empty = 1; //����ũ 1 ������� o
	oneserv.service_time = 0; //����ũ 1 ó���ϴ� �մ��� �ð� 0 ����
	oneserv.service_customer = 0; //����ũ 1 ó���ϴ� �մ��� ���̵� 0 ����
	
	twoserv.empty = 1; //����ũ 2 ������� o
	twoserv.service_time = 0; //����ũ 2 ó���ϴ� �մ��� �ð� 0 ����
	twoserv.service_customer = 0; //����ũ 2 ó���ϴ� �մ��� ���̵� 0 ����
	
	
	init_queue(&queue); //ť �ʱ⼳��
	srand(time(NULL)); //���� �����

	for (int clock1 = 0; clock1 < minutes; clock1++) { //�ð� ���� �뵵, �� �и��� �մ��� �� Ȯ���� ���� �մ��� ����
		//����ũ1, ����ũ2���� �մ��� ó���Ѵ�.

		
		printf("*************************\n\n");
		
		printf("����ð� = %d\n", clock1); //����ð� �˸�
		if ((rand() % 10) < 3) { //0���� 9���� ������ ���ڸ� �̾� 3���� ������ �մ��� �´�. Ȯ���� 10 / 3 �̴�.

			client customer; //�մ� ����
			customer.id = total_customers++; //������� �� �մ� ���ڷ� ��ȣ�� ���̵� �ο��� �� �� �մ��� �� ���ʴ�� ������ �ο��Ѵ�.
			customer.arrival_time = clock1; //�մ��� �� �ð��� ����Ѵ�.
			customer.service_time = rand() % 3 + 1; //1���� 3���� ������ ���ڸ� �̾� �ʿ伭�񽺽ð����� �����Ѵ�.
			enqueue(&queue, customer); //ť�� �ִ´�.
			printf("�� [[%d]]�� %d�п� ���ɴϴ�. ���ð� = %d��\n\n", 
				customer.id, customer.arrival_time, customer.service_time); //���� ����(���̵�, �½ð�, �ʿ伭�񽺽ð�)�� ������ش�.
		
		}
		
			
			if (!is_empty(&queue) && oneserv.empty == 1) { //ť�� �մ��� �ְ� ����ũ 1�� ����� ��
				client customer = dequeue(&queue); //ť���� ���� ������ �Ѵ�.
				printf("�� [[%d]]�� %d�п� **1 ����ũ**���� ������ �����մϴ�. ���ð��� %d���̾����ϴ�.\n",
					customer.id, clock1, clock1 - customer.arrival_time); //���� ����(���̵�, ����ð�, ��ٸ� �ð�)�� ������ش�.
				oneserv.service_customer = customer.id; //����ũ 1�� ó���� ���� ���̵� ����
				oneserv.service_time = customer.service_time; //����ũ 1�� ó���� ���� �ʿ�ð�����
				oneserv.empty = 0; //����ũ 1�� ��� �Ұ��� ����
				total_wait += clock1 - customer.arrival_time; //��ü ���ð��� �մ��� ���ð� ����
					
			}

			if (!is_empty(&queue) && twoserv.empty == 1) {//ť�� �մ��� �ְ� ����ũ 2�� ����� �� //1�� �����ϰ� �۵�
				client customer = dequeue(&queue);
				printf("�� [[%d]]�� %d�п� **2 ����ũ**���� ������ �����մϴ�. ���ð��� %d���̾����ϴ�.\n",
					customer.id, clock1, clock1 - customer.arrival_time);
				twoserv.service_customer = customer.id;
				twoserv.service_time = customer.service_time;
				twoserv.empty = 0;

				total_wait += clock1 - customer.arrival_time;

			}

			if (oneserv.service_time >= 1){ //1���� ó���ʿ�ð��� ������ ��

				printf("�� [[%d]] **1 ����ũ**���� %d�� ���ҽ��ϴ�. \n", oneserv.service_customer, oneserv.service_time);
				//1�� ó������ �մ� ��� ���Ҵ��� ���
	
				printf("********1 ����ũ�� ����� �Ұ����մϴ�.\n\n");
				oneserv.service_time--;
				//1�� ó������ �ð� ����

				if (oneserv.service_time == 0) { //���� �ð��� 0�� �� ��
					printf("�� [[%d]] **1 ����ũ**���� ����� �������ϴ�. \n\n", oneserv.service_customer); //���� �˸�
					oneserv.empty = 1; //����ũ 1 ��
					total_finished_customers++; //ó���� �մ� ����++
				}

			}

			if (twoserv.service_time >= 1) { //2���� ó���ʿ�ð��� ������ �� //1�� ���� �۵�
			
				printf("�� [[%d]] **2 ����ũ**���� %d�� ���ҽ��ϴ�. \n", twoserv.service_customer, twoserv.service_time);

				printf("********2 ����ũ�� ����� �Ұ����մϴ�.\n\n");
				twoserv.service_time--;

				if (twoserv.service_time == 0) {
					printf("�� [[%d]] **2 ����ũ**���� ����� �������ϴ�. \n\n", twoserv.service_customer);
					twoserv.empty = 1;
					total_finished_customers++;
				}

			}	

	}
	printf("��ü ��� �ð� = %d�� \n", total_wait); //��ü �湮�� �մ��� ���ð� ���
	printf("��ü �湮�� �� ó���Ϸ��� �湮�� �� = %d ��\n", total_finished_customers); //�ð��� �� �Ǿ� �湮�� �� �� ó���� ��� ������� Ȯ�ο�
	return 0;
}