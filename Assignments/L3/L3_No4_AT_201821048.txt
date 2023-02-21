#include <stdio.h>
#include <stdlib.h>
/*
L3_No4_AT_201821048.c
이서영
syjy8809@gmail.com
L3_No4
기존 링크드리스트에서 몇번째에 있는 노드의 값을
추가하거나 뺴는 함수 추가해 사용하기
교수님이 과제로 올려주신 코드를 기반으로 사용
10월 6일 최종수정
*/

typedef int element; //올려주신 코드
typedef struct ListNode { 	//올려주신 코드
	element data;
	struct ListNode* link;
} ListNode;

// 오류 처리 함수
void error(char* message) //올려주신 코드
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

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

	ListNode* position = (ListNode*)malloc(sizeof(ListNode));
	//position 선언
	position = head; //앞부분 가르키게 함
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
		for (; count == pos; count++) { //count를 pos만큼 키우면서
			position = position->link; //그 횟수만큼 position의 위치를 이동시킨다.
		}
	}
	return position; //찾아진 position의 값을 반환한다.
}

ListNode* add_entry_at(ListNode* head, int position, int item) {
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

ListNode* insert_first(ListNode* head, int value) //올려주신 코드
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)
	p->data = value;					// (2)
	p->link = head;	// 헤드 포인터의 값을 복사	//(3)
	head = p;	// 헤드 포인터 변경		//(4)
	return head;	// 변경된 헤드 포인터 반환
}

// 노드 pre 뒤에 새로운 노드 삽입 //올려주신 코드
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

ListNode* delete_first(ListNode* head) //올려주신 코드
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;	// (1)
	head = removed->link;	// (2)
	free(removed);		// (3)
	return head;		// (4)
}
// pre가 가리키는 노드의 다음 노드를 삭제한다. 
ListNode* delete(ListNode* head, ListNode* pre) //올려주신 코드
{
	ListNode* removed;
	removed = pre->link; //1
	pre->link = removed->link;		// (2)
	free(removed);			// (3)
	return head;			// (4)
}

void print_list(ListNode* head) //올려주신 코드
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}

// 테스트 프로그램 과제에서 지정한 메인
int main(void)
{
	ListNode* head = NULL;
	element data;

	for (int i = 0; i < 2; i++) {
		data = i * 10;
		head = add_entry_at(head, i, data);
		print_list(head);
	}
	for (int i = 2; i < 4; i++) {
		data = i + 10;
		head = add_entry_at(head, i, data);
		print_list(head);
	}
	for (int i = 2; i >= 0; i--) {
		head = delete_node_at(head, i);
		print_list(head);
	}
	return 0;
}