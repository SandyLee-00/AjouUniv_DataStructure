/*
교재 13.2, 4, 5, 6, 7 참고함
이서영 2019/12/04
순차탐색, 재귀 이진탐색, 반복 이진탐색, 색인탐색, 보간탐색
*/
#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, t) ((t) = (x),(x) = (y),(y) = (t))
#define INDEX_SIZE 10
#define LIST_SIZE 100

typedef struct{
	int key;
	int index;
}itable;

list[LIST_SIZE];

itable index_list[INDEX_SIZE];


int seq_search(int key, int low, int high)
//13.1 순차탐색
{
	int i;
	for (i = low; i <= high; i++)
		if (list[i] == key)
			return i;  // 탐색에 성공하면 키 값의 인덱스 반환 
	return -1;    // 탐색에 실패하면 -1 반환 
}


int search_binary(int key, int low, int high)
//13.4 순환 탐색을 이용한 이진탐색
{
	int middle;
	if (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])    // 탐색 성공
			return middle;
		else if (key < list[middle]) // 왼쪽 부분리스트 탐색 
			return search_binary(key, low, middle - 1);
		else                   // 오른쪽 부분리스트 탐색 
			return search_binary(key, middle + 1, high);
	}
	return -1;        // 탐색 실패
}

int search_binary2(int key, int low, int high)
//반복을 이용한 이진탐색
{
	int middle;

	while (low <= high) {       // 아직 숫자들이 남아 있으면
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key > list[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}
	return -1;   // 발견되지 않음 
}

// INDEX_SIZE는 인덱스 테이블의 크기,n은 전체 데이터의 수 
int search_index(int key)
//13.6 색인 순차 탐색
{
	int i, low, high;
	// 키 값이 리스트 범위 내의 값이 아니면 탐색 종료

	if (key<list[0] || key>list[LIST_SIZE - 1])
		return -1;

	// 인덱스 테이블을 조사하여 해당키의 구간 결정
	for (i = 0; i < LIST_SIZE; i++)
		if (index_list[i].key <= key &&
			index_list[i + 1].key > key)
			break; 
	if (i == INDEX_SIZE) {  // 인덱스테이블의 끝이면 
		low = index_list[i - 1].key;
		high = LIST_SIZE;
	}
	else {
		low = index_list[i].key;
		high = index_list[i + 1].key;
	}
	printf("llow=>%d high=>%d", low, high);
	// 예상되는 범위만 순차 탐색 
	return seq_search(key, low, high);
}

//
int search_interpolation(int key, int n)
//13.7 보간탐색
{
	int low, high, j;
	low = 0;
	high = n - 1;
	while ((list[high] >= key) && (key > list[low])) {
		j = ((float)(key - list[low]) / (list[high] - list[low])
			* (high - low)) + low;
		if (key > list[j]) low = j + 1;
		else if (key < list[j]) high = j - 1;
		else low = j;
	}
	if (list[low] == key) return(low);  // 탐색성공
	else return -1;  // 탐색실패
}

int main() {
	for (int i = 0; i < LIST_SIZE; i++) {
		list[i] = i;
		printf("%d\n", i);
	}
	for (int i = 0; i < INDEX_SIZE; i++) {
		index_list[i].index = i;
		index_list[i].key = i * 10;
	}
	int seq_search_v = seq_search(5, 0, LIST_SIZE-1);
	int search_binary_v = search_binary(5, 0, LIST_SIZE - 1);
	int search_binary2_v = search_binary2(5, 0, LIST_SIZE - 1);
	int search_index_v = search_index(5);
	int search_interpolation_v = search_interpolation(5, LIST_SIZE);
	
	//5이면 성공 -1이면 실패
	printf("seq_search_v : %d\n", list[seq_search_v]);
	printf("search_binary_v : %d\n", list[search_binary_v]);
	printf("search_binary2_v : %d\n", list[search_binary2_v]);
	printf("search_index_v : %d\n", list[search_index_v]);
	printf("search_interpolation_v : %d\n", list[search_interpolation_v]);
}


