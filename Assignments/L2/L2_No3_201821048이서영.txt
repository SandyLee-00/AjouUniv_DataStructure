#define _CRT_SECURE_NO_WARNINGS
/* Program 5.2 in p.157 C언어로 쉽게 풀어쓴 자료구조, 개정3판, 천인국 등 저, 생능출판사 
*/
/*
File Name : L2_No3_201821048_201821048.c
Author : Lee Seoyeong
Email : syjy8809@gmail.com
Lab Number & Problem Number : L2_No3
Description : 원형큐를 출력하는 프로그램에서 개수를 출력하는 기능 추가하기
References : Program 5.2 in p.157 C언어로 쉽게 풀어쓴 자료구조, 개정3판, 천인국 등 저, 생능출판사
Last Changed: September 25, 2019
*/

 #include <stdio.h>
 #include <stdlib.h>
 #define MAX_QUEUE_SIZE 5 //원형 큐 전체 사이즈 5, 사용가능 4칸

typedef int element; //int 형의 데이터 넣음

typedef struct { //원형 큐를 배열로 구현함, 5사이즈에 앞부분 front 마지막 rear을 설정함
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

 void error(char* message);
 void init_queue(QueueType * q);
 int is_empty(QueueType * q);
 int is_full(QueueType * q);
 void enqueue(QueueType * q, element item);
 element dequeue(QueueType * q);
 element peek(QueueType * q);
 void queue_print(QueueType * q);
 int get_count(QueueType* q);

 // 오류함수
 void error(char* message)
 {
	 fprintf(stderr, "%s\n", message);
	 exit(1);
	 }

 // 초기화 함수
 void init_queue(QueueType * q) //앞과 뒤를 0으로 초기설정함
 {
	 q->front = q->rear = 0;
	 }

 // 공백 상태 검출 함수
 int is_empty(QueueType * q) //비었는지 확인, 앞과 뒤가 만나면 비었음에 1, 아님 0
 {
	 return (q->front == q->rear);
	 }

 int is_full(QueueType * q) //찼는지 확인, 앞과 ((뒤 + 1)에 모듈러 한 값)이 같으면 사용가능한 칸 전부 찼음
 {
	 return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
	 }

 int get_count(QueueType* q) { //뒤 - 앞, 앞은 빈 칸을 가리키기 때문

	 int count = (q->rear % MAX_QUEUE_SIZE) - (q->front % MAX_QUEUE_SIZE);
	 if (count < 0) { //한바퀴를 돌아 rear의 숫자가 front 보다 작아지면 -가 된다. 그래서 그만큼 비어있으니까 전체 - 빈칸을 해서 찬 칸을 센다.
		 count = MAX_QUEUE_SIZE - count;
	 }
	 return count;
 }

 void queue_print(QueueType * q) //큐 출력해줌
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
 void enqueue(QueueType * q, element item)
	 {
	 //삽입 알고리즘
		 if (is_full(q))
		 error(" 큐가 포화상태입니다\n"); //찼으면 포화메시지 출력
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; //rear 한칸뒤로가기 (모듈러)
	q->data[q->rear] = item; //그 칸에 새로운 데이터 넣기
	 }

 // 삭제 함수
 element dequeue(QueueType * q)
 {
	 //삭제 알고리즘
		 if (is_empty(q)) //비었으면 공백메시지 출력
		 error(" 큐가 공백상태입니다\n");
	 q->front = (q->front + 1) % MAX_QUEUE_SIZE; //front 큐에 찬 칸으로 이동 (모듈러);
	 return q->data[q->front]; //위에 칸의 값 반환
	 }

 // peek 함수
 element peek(QueueType * q) //앞 보기
 {
	 if (is_empty(q))
		 error("큐가 공백상태입니다"); //없으면 에러
	 return q->data[(q->front + 1) % MAX_QUEUE_SIZE]; //앞에 찬칸 데이터 반환

	 }

 int main() //교수님이 올려주신 코드
 {
	 QueueType q; //q를 만듦
	 int element; //데이터 입력용
	
		 init_queue(&q); //q 
	 printf("--데이터 추가 단계--\n");
	 while (!is_full(&q))
		 {
		 printf("정수를 입력하시오: ");
		scanf_s("%d", &element);
		 enqueue(&q, element);
		 queue_print(&q);
		}
	 printf("큐 포화상태\n\n");
	
		 printf("--데이터 삭제 단계--\n");
	 while (!is_empty(&q))
		 {
		 element = dequeue(&q);
		 printf("꺼내진 정수: %d \n", element);
		 queue_print(&q);
		 }
	 printf("큐는 공백상태\n");
	return 0;
	 }