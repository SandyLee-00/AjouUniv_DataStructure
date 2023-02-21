/*  */
/*
File Name : L2_No4_201821048.c
Lee Seoyeong
L2_No4
은행 2개의 데스크에서 큐에서 기다리는 사람들을 뽑아 각각 일을 처리한다.
Program 5.5 in p.169 C언어로 쉽게 풀어쓴 자료구조, 개정3판, 천인국 등 저, 생능출판사
September 29, 2019
*/

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <stdbool.h>

#define MAX_QUEUE_SIZE 10 //9명까지 대기가능
#define minutes 30 //수행시간


 // 프로그램 5.2에서 다음과 같은 부분을 복사한다.
 // ================ 원형큐 코드 시작 =================
typedef struct { // 요소 타입 //교수님이 주신 부분
	 int id;
	 int arrival_time;
	 int service_time;
} client; 

typedef struct { //원형 큐를 배열로 구현함, 5사이즈에 앞부분 front 마지막 rear을 설정함
	client data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

typedef struct { //은행원이 각 데스크에서 처리하도록 Server_able 타입을 만들었다.
	bool empty; //처리하는 데스크가 비었는지 확인용 비었으면 1, 처리중이면 0
	int service_time; //처리하는 손님의 필요서비스 시간저장
	int service_customer; //처리하는 손님의 아이디 저장
}Server_able;
/*이 밑의 큐 구현부분은 교수님이 주신 L2_No3과제에서 갖고옴
*/

void init_queue(QueueType* q);
int is_empty(QueueType* q);
int is_full(QueueType* q);
void enqueue(QueueType* q, client item);
client dequeue(QueueType* q);
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


// 삽입 함수
void enqueue(QueueType* q, client item)
{
	//삽입 알고리즘
	if (is_full(q))
		printf(" 큐가 포화상태입니다\n"); //찼으면 포화메시지 출력
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; //rear 한칸뒤로가기 (모듈러)
	q->data[q->rear] = item; //그 칸에 새로운 데이터 넣기
}

// 삭제 함수
client dequeue(QueueType* q)
{
	//삭제 알고리즘
	if (is_empty(q)) //비었으면 공백메시지 출력
		printf(" 큐가 공백상태입니다\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; //front 큐에 찬 칸으로 이동 (모듈러);
	return q->data[q->front]; //위에 칸의 값 반환
}




// ================ 원형큐 코드 종료 =================


int main(void) //교수님이 주신 부분
{
	int total_wait = 0; //전체 손님 대기시간 카운트
	int total_customers = 0; //전체 방문 손님 수 카운트
	int total_finished_customers = 0; ////전체 처리한 손님 수 카운트, 시간이 되어 불가능하면 세지 않는다.

	QueueType queue; //대기 장소 큐 생성
	Server_able oneserv; //처리 장소 데스크 1 생성
	Server_able twoserv; //처리 장소 데스크 2 생성

	oneserv.empty = 1; //데스크 1 비어있음 o
	oneserv.service_time = 0; //데스크 1 처리하는 손님의 시간 0 설정
	oneserv.service_customer = 0; //데스크 1 처리하는 손님의 아이디 0 설정
	
	twoserv.empty = 1; //데스크 2 비어있음 o
	twoserv.service_time = 0; //데스크 2 처리하는 손님의 시간 0 설정
	twoserv.service_customer = 0; //데스크 2 처리하는 손님의 아이디 0 설정
	
	
	init_queue(&queue); //큐 초기설정
	srand(time(NULL)); //랜덤 사용함

	for (int clock1 = 0; clock1 < minutes; clock1++) { //시간 세는 용도, 매 분마다 손님이 올 확률에 따라 손님이 오고
		//데스크1, 데스크2에서 손님을 처리한다.

		
		printf("*************************\n\n");
		
		printf("현재시각 = %d\n", clock1); //현재시간 알림
		if ((rand() % 10) < 3) { //0부터 9까지 랜덤한 숫자를 뽑아 3보다 작으면 손님이 온다. 확률은 10 / 3 이다.

			client customer; //손님 만듦
			customer.id = total_customers++; //현재까지 온 손님 숫자로 번호를 아이디에 부여한 후 총 손님을 해 차례대로 순서를 부여한다.
			customer.arrival_time = clock1; //손님이 온 시간을 기록한다.
			customer.service_time = rand() % 3 + 1; //1부터 3까지 랜덤한 숫자를 뽑아 필요서비스시간으로 설정한다.
			enqueue(&queue, customer); //큐에 넣는다.
			printf("고객 [[%d]]이 %d분에 들어옵니다. 사용시간 = %d분\n\n", 
				customer.id, customer.arrival_time, customer.service_time); //고객의 정보(아이디, 온시간, 필요서비스시간)을 출력해준다.
		
		}
		
			
			if (!is_empty(&queue) && oneserv.empty == 1) { //큐에 손님이 있고 데스크 1이 비었을 때
				client customer = dequeue(&queue); //큐에서 빼내 업무를 한다.
				printf("고객 [[%d]]이 %d분에 **1 데스크**에서 업무를 시작합니다. 대기시간은 %d분이었습니다.\n",
					customer.id, clock1, clock1 - customer.arrival_time); //고객의 정보(아이디, 현재시간, 기다린 시간)을 출력해준다.
				oneserv.service_customer = customer.id; //데스크 1이 처리할 고객의 아이디 저장
				oneserv.service_time = customer.service_time; //데스크 1이 처리할 고객의 필요시간저장
				oneserv.empty = 0; //데스크 1을 사용 불가능 설정
				total_wait += clock1 - customer.arrival_time; //전체 대기시간에 손님의 대기시간 저장
					
			}

			if (!is_empty(&queue) && twoserv.empty == 1) {//큐에 손님이 있고 데스크 2이 비었을 때 //1과 동일하게 작동
				client customer = dequeue(&queue);
				printf("고객 [[%d]]이 %d분에 **2 데스크**에서 업무를 시작합니다. 대기시간은 %d분이었습니다.\n",
					customer.id, clock1, clock1 - customer.arrival_time);
				twoserv.service_customer = customer.id;
				twoserv.service_time = customer.service_time;
				twoserv.empty = 0;

				total_wait += clock1 - customer.arrival_time;

			}

			if (oneserv.service_time >= 1){ //1에서 처리필요시간이 남았을 때

				printf("고객 [[%d]] **1 데스크**에서 %d분 남았습니다. \n", oneserv.service_customer, oneserv.service_time);
				//1이 처리중인 손님 몇분 남았는지 출력
	
				printf("********1 데스크는 사용이 불가능합니다.\n\n");
				oneserv.service_time--;
				//1이 처리중인 시간 빼기

				if (oneserv.service_time == 0) { //서비스 시간이 0이 될 때
					printf("고객 [[%d]] **1 데스크**에서 사용이 끝났습니다. \n\n", oneserv.service_customer); //끝남 알림
					oneserv.empty = 1; //데스크 1 빔
					total_finished_customers++; //처리한 손님 숫자++
				}

			}

			if (twoserv.service_time >= 1) { //2에서 처리필요시간이 남았을 때 //1과 동일 작동
			
				printf("고객 [[%d]] **2 데스크**에서 %d분 남았습니다. \n", twoserv.service_customer, twoserv.service_time);

				printf("********2 데스크는 사용이 불가능합니다.\n\n");
				twoserv.service_time--;

				if (twoserv.service_time == 0) {
					printf("고객 [[%d]] **2 데스크**에서 사용이 끝났습니다. \n\n", twoserv.service_customer);
					twoserv.empty = 1;
					total_finished_customers++;
				}

			}	

	}
	printf("전체 대기 시간 = %d분 \n", total_wait); //전체 방문한 손님의 대기시간 출력
	printf("전체 방문자 중 처리완료한 방문자 수 = %d 명\n", total_finished_customers); //시간이 다 되어 방문자 중 못 처리한 사람 생기는지 확인용
	return 0;
}