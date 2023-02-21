#include <stdio.h>
#include <stdlib.h>
/*
HW1
다음과 같이 단순 연결 리스트에 사용자가 입력하는 값을 저장했다가 출력하고, 저장된 데이터들의 평균값을 출력하는 프로그램을 작성하시오.

Hw1_No1
이서영
syjy8809@gmail.com
Hw1_No1
다음과 같이 단순 연결 리스트에 사용자가 입력하는 값을 저장했다가 출력하고, 저장된 데이터들의 평균값을 출력하는 프로그램을 작성하시오.
2019/10/13
*/

typedef int element; //과제 3에서 올려주신 코드
typedef struct ListNode { 	//과제 3에서 올려주신 코드
	element data;
	struct ListNode* link;
} ListNode;


int get_length(ListNode* head) { //링크드리스트 길이구하기

	int count = 0; //숫자세기
	for (ListNode* p = head; p != NULL; p = p->link) {
		count++; //for문으로 처음부터 끝까지 돌면서 개수++
	}
	return count; //int형으로 길이 반환
}

ListNode* get_node_at(ListNode* head, int pos) {
	//링크드리스트인 head와 위치인 pos값을 넣어
	//그 위치인 position을 반환한다.

	ListNode* position = head;
	//position 선언
	//앞부분 가르키게 함
	int length = get_length(head); //링크드 리스트 길이 구하기
	int count = 0;
	if (length < pos) { //리스트의 길이보다 큰 위치에 넣었으면
		printf("리스트의 길이보다 큰 위치에 넣었다.");
		exit(1); //프로그램 종료
		return NULL;
	}
	if (pos == 0) { //구하려는 위치가 첫번째이면 head를 반환
		return position;
	}
	if (pos <= 0) { //-위치를 찾는다고 할 경우
		printf("0보다 작거나 같은 위치를 넣었다.");
		exit(1); //프로그램 종료
		return NULL;
	}
	if (pos > 0 && length >= pos) { //리스트의 길이보다 작거나 같은 위치이고 
		//두번째 이상 위치를 찾는 경우
		for (; count != pos; count++) { //count를 pos만큼 키우면서
			position = position->link; //그 횟수만큼 position의 위치를 이동시킨다.
		}
		return position; //찾아진 position의 값을 반환한다.
	}
	
}

ListNode* add_entry_at(ListNode* head, int position, element item) {
	//head를 넣고 get_node_at를 이용해 pre를 찾는다.

	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	//집어넣을 노드 생성

	p->data = item; //데이터를 해당 노드에 넣기

	if (position == 0) { //만약 head에 넣을 경우
		//insert_first와 동일처리
		p->link = head;	// 헤드 포인터의 값을 복사	//(3)
		head = p;	// 헤드 포인터 변경		//(4)
		return head;	// 변경된 헤드 포인터 반환
	}
	if (position > 0) { //head가 아닐 경우 
		//insert함수와 동일처리
		ListNode* pre = (ListNode*)malloc(sizeof(ListNode));
		pre = get_node_at(head, (position - 1));
		//get_node_at에서 오류처리 해줌
		p->link = pre->link;	//(3)	
		pre->link = p;		//(4)	
		return head;		//(5)
	}
}

ListNode* insert_first(ListNode* head, int value) //과제 3에서 올려주신 코드
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)
	p->data = value;					// (2)
	p->link = head;	// 헤드 포인터의 값을 복사	//(3)
	head = p;	// 헤드 포인터 변경		//(4)
	return head;	// 변경된 헤드 포인터 반환
}

// 노드 pre 뒤에 새로운 노드 삽입 //과제 3에서 올려주신 코드
ListNode* insert(ListNode* head, ListNode* pre, int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)
	p->data = value;		//(2)
	p->link = pre->link;	//(3)	
	pre->link = p;		//(4)	
	return head;		//(5)	
}

ListNode* delete_node_at(ListNode* head, int position) {
	//head를 넣고 get_node_at를 이용해 pre를 찾는다.
	ListNode* removed;
	//뺄 노드 생성
	if (position == 0) { //만약 head에 넣을 경우
		//delete_first와 동일처리
		if (head == NULL) return NULL;
		removed = head;	// (1)
		head = removed->link;	// (2)
		free(removed);		// (3)
		return head;		// (4)
	}
	if (position > 0) { //head가 아닐 경우 
		//delete 함수와 동일처리
		ListNode* pre = (ListNode*)malloc(sizeof(ListNode));
		pre = get_node_at(head, position);
		//get_node_at에서 오류처리 해줌
		removed = pre->link; //1
		pre->link = removed->link;		// (2)
		free(removed);			// (3)
		return head;			// (4)
	}
}

ListNode* delete_first(ListNode* head) //과제 3에서 올려주신 코드
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;	// (1)
	head = removed->link;	// (2)
	free(removed);		// (3)
	return head;		// (4)
}
// pre가 가리키는 노드의 다음 노드를 삭제한다. 
ListNode* delete(ListNode* head, ListNode* pre) //과제 3에서 올려주신 코드
{
	ListNode* removed;
	removed = pre->link; //1
	pre->link = removed->link;		// (2)
	free(removed);			// (3)
	return head;			// (4)
}

void print_list(ListNode* head) //과제 3에서 올려주신 코드 수정
{
	double average = 0; //평균 변수
	int count = 0; //숫자세기
	for (ListNode* p = head; p != NULL; p = p->link) {
		//head부터 p가 널이 될때까지 돌린다
		printf("%d_", p->data); //p데이터 출력
		average = average + p->data; //평균에 계속 더하기
		count++; //횟수 카운트
	}
	average = average / count; //총 합을 횟수로 나눠 평균 구하기
	printf("\n%.1lf\n", average); //첫째자리까지 평균 출력하기
}


int main(void)
{
	ListNode* head = NULL;
	element data = 0;
	int numof_inputdata; //입력데이터 개수
	scanf_s("%d", &numof_inputdata); //입력데이터 개수 입력받기

	for (int i = 0; i < numof_inputdata; i++) {//입력 데이터 개수만큼 돌기
		scanf_s("%d", &data); //사용자가 데이터 입력
		head = add_entry_at(head, i, data);
	}//0위치부터 차례대로 데이터 넣기

	print_list(head); //데이터 출력

	return 0;
}