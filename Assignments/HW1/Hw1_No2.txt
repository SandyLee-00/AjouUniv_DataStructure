#include <stdio.h>
#include <stdlib.h>
/*
HW2

Hw1_No2
이서영
syjy8809@gmail.com
Hw1_No2
단순 연결 리스트가 정렬되지 않은 두 개 이상의 정수들의 리스트를 저장하고 있다. 
리스트에서 최대값을 찾아 출력하고, 
최대값을 리스트에서 삭제하여 변형된 리스트를 출력하는 프로그램을 작성하시오.
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
	//double average = 0; //평균 변수
	int count = 0; //숫자세기
	for (ListNode* p = head; p != NULL; p = p->link) {
		//head부터 p가 널이 될때까지 돌린다
		printf("%d_", p->data); //p데이터 출력
		//average = average + p->data; //평균에 계속 더하기
		count++; //횟수 카운트
	}
	//average = average / count; //총 합을 횟수로 나눠 평균 구하기
	//printf("\n%.1lf\n", average); //첫째자리까지 평균 출력하기
}

int where_is_the_data(ListNode* head, int biggest) { //데이터 어디있는지 찾기
	//가장 큰 값의 위치를 0부터 시작해 알려준다
	int biggest_pos = 0;
	for (ListNode* p = head; p != NULL; p = p->link) {
		//head부터 p가 널이 될때까지 돌린다
		biggest_pos++; //몇번째인지 세주기
		if (biggest == p->data) { //데이터가 최댓값이면
			return biggest_pos; //위치 반환
		}
	}
}

int find_biggest(ListNode* head) {

	int biggest = head->data; //가장 큰 값
	int biggest_pos = 0; //큰 값의 위치
	
	for (ListNode* p = head; p != NULL; p = p->link) {
		//head부터 p가 널이 될때까지 돌린다
		if (biggest < p->data) { //데이터보다 작으면
			biggest = p->data; //큰 값 수정저장
		}
	}
	printf("\n%d이 가장 큰 값이다.\n", biggest); //큰값출력
	biggest_pos = where_is_the_data(head, biggest) - 1; //데이터위치찾는함수사용
	//위의 함수에서 1부터 시작해서 0부터 위치 표현하도록 -1 해서 수정해줌
	printf("\n%d위치에 가장 큰 값이 있어 삭제한다.(0부터 시작)\n", biggest_pos); //0기준위치 출력
	return biggest_pos;
}

ListNode* delete_biggest(ListNode* head, int biggest_pos) {
	//위에서 받아온 최댓값 위치 넣어서 지워주기
	ListNode* removed;

	if (biggest_pos == 0) { //위에있는 첫번째노드를 삭제코드 복사
		removed = head;	// (1)
		head = removed->link;	// (2)
		free(removed);		// (3)
		return head;
	}
	else { //위에있는 pre뒤에있는 것 삭제코드 복사
		ListNode* pre = get_node_at(head, biggest_pos - 1);
		//pre를 선언해 그 전 위치 노드 알아와야함
		removed = pre->link; //1
		pre->link = removed->link;		// (2)
		free(removed);			// (3)
		return head;			// (4)
	}
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

	int biggest_pos = find_biggest(head); //가장 큰 값 출력, 큰값 위치 반환
	head = delete_biggest(head, biggest_pos); //가장 큰 값 지우기
	
	print_list(head); //데이터 출력

	return 0;
}