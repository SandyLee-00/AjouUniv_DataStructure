/* Program 5.5 in p.169 C언어로 쉽게 풀어쓴 자료구조, 개정3판, 천인국 등 저, 생능출판사 */

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

#define MAX_SIZE = 10; //9명까지 대기가능

 // 프로그램 5.2에서 다음과 같은 부분을 복사한다.
 // ================ 원형큐 코드 시작 =================
typedef struct { // 요소 타입 //교수님이 주신 부분
	10 int id;
	11 int arrival_time;
	12 int service_time;
	13
} element; // 교체!



typedef struct { //원형 큐를 배열로 구현함, 5사이즈에 앞부분 front 마지막 rear을 설정함
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

void init_queue(QueueType* q) //앞과 뒤를 0으로 초기설정함//교수님이 문제 3에서 주심
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q) //비었는지 확인, 앞과 뒤가 만나면 비었음에 1, 아님 0//교수님이 문제 3에서 주심
{
	return (q->front == q->rear);
}

int is_full(QueueType* q) //찼는지 확인, 앞과 ((뒤 + 1)에 모듈러 한 값)이 같으면 사용가능한 칸 전부 찼음//교수님이 문제 3에서 주심
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
int get_count(QueueType* q) { //뒤 - 앞, 앞은 빈 칸을 가리키기 때문//문제 3에서 사용

	int count = (q->rear % MAX_QUEUE_SIZE) - (q->front % MAX_QUEUE_SIZE);
	if (count < 0) { //한바퀴를 돌아 rear의 숫자가 front 보다 작아지면 -가 된다. 그래서 그만큼 비어있으니까 전체 - 빈칸을 해서 찬 칸을 센다.
		count = MAX_QUEUE_SIZE - count;
	}
	return count;
}

void queue_print(QueueType* q) //큐 출력해줌
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear); //front와 rear 위치 출력
	if (!is_empty(q)) { //비어있지 않으면
		int i = q->front; //i에 front 저장
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE); //front + 1해서 찬 칸으로 이동 후 모듈러 연산
			printf("%d|", q->data[i]); //위에 칸 데이터 출력
			if (i == q->rear) //rear까지 출력하면 끝내기
				break;

		} while (i != q->front); //그 칸이 front이면 안된다.(전 줄의 break로 빠져나간다.)

	}
	printf("\n"); //띄어쓰기

	printf("%d\n", get_count(q)); //getcount로 원형큐에 들어있는 것도 출력해준다.
}

// 삽입 함수
void enqueue(QueueType* q, element item)
{
	//삽입 알고리즘
	if (is_full(q))
		error(" 큐가 포화상태입니다\n"); //찼으면 포화메시지 출력
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; //rear 한칸뒤로가기 (모듈러)
	q->data[q->rear] = item; //그 칸에 새로운 데이터 넣기
}

// 삭제 함수
element dequeue(QueueType* q)
{
	//삭제 알고리즘
	if (is_empty(q)) //비었으면 공백메시지 출력
		error(" 큐가 공백상태입니다\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; //front 큐에 찬 칸으로 이동 (모듈러);
	return q->data[q->front]; //위에 칸의 값 반환
}

// peek 함수
element peek(QueueType* q) //앞 보기
{
	if (is_empty(q))
		error("큐가 공백상태입니다"); //없으면 에러
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE]; //앞에 찬칸 데이터 반환

}


// ================ 원형큐 코드 종료 =================


int main(void) //교수님이 주신 부분
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
		printf("현재시각=%d\n", clock);
		if ((rand() % 10) < 3) {
			element customer;
			customer.id = total_customers++;
			customer.arrival_time = clock;
			customer.service_time = rand() % 3 + 1;
			enqueue(&queue, customer);
			printf("고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n",
				customer.id, customer.arrival_time, customer.service_time);

		}
		if (service_time > 0) {
			printf("고객 %d 업무처리중입니다. \n", service_customer);
			service_time--;

		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다.\n",
					customer.id, clock, clock - customer.arrival_time);
				total_wait += clock - customer.arrival_time;

			}

		}

	}
	printf("전체 대기 시간=%d분 \n", total_wait);
	return 0;
}