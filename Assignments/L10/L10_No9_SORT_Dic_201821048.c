/* 천인국, 공용해, 하상호 지음, C언어로 쉽게 풀어쓴 자료구조(개정3판), 생능출판 사. 프로그램 12.6 */
/* 천인국, 공용해, 하상호 지음, C언어로 쉽게 풀어쓴 자료구조(개정3판), 생능출판 사. 프로그램 12.11 */

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <string.h>
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) ) 
#define MAX_WORD_SIZE 50 
#define MAX_MEANING_SIZE 500 
#define SIZE 5
#define MAX_SIZE 99999

typedef struct {
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
}element;

element list[SIZE];    /* 구조체 배열 선언 */
element sorted[MAX_SIZE];   // 추가 공간이 필요

/* i는 정렬된 왼쪽 리스트에 대한 인덱스  j는 정렬된 오른쪽 리스트에 대한 인덱스  k는 정렬될 리스트에 대한 인덱스 */
void merge(element list[], int left, int mid, int right) {
	int left_i, mid_j, left_k, l;
	left_i = left;
	mid_j = mid + 1;
	left_k = left;
	/* 분할 정렬된 list의 합병 */
	while (left_i <= mid && mid_j <= right) {
		if (strcmp(list[left_i].word, list[mid_j].word) < 0)
			sorted[left_k++] = list[left_i++];
		else   sorted[left_k++] = list[mid_j++];

	}
	if (left_i > mid)
		/* 남아 있는 레코드의 일괄 복사 */
		for (l = mid_j; l <= right; l++)
			sorted[left_k++] = list[l];
	else
		/* 남아 있는 레코드의 일괄 복사 */
		for (l = left_i; l <= mid; l++)
			sorted[left_k++] = list[l];
	/* 배열 sorted[]의 리스트를 배열 list[]로 재복사 */
	for (l = left; l <= right; l++)
		list[l] = sorted[l];

} // 
void merge_sort(element list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		/* 리스트의 균등 분할 */
		merge_sort(list, left, mid);
		/* 부분 리스트 정렬 */
		merge_sort(list, mid + 1, right);
		/* 부분 리스트 정렬 */
		merge(list, left, mid, right);
		/* 합병 */

	}

}

int main() {

	printf("5개의 단어와 의미를 입력하시오\n");

	for (int i = 0; i < SIZE; i++) {
		scanf("%s[^\n]", list[i].word); // 엔터키만을 제외하고 받는다.  
		scanf("%s[^\n]", list[i].meaning);// 엔터키만을 제외하고 받는다. 
	}
	// 버블 정렬 
	/*
	for (i = 0; i < SIZE - 1; ++i) {
		for (j = i + 1; j < SIZE; ++j) {
			if (strcmp(list[i].word, list[j].word) > 0) {
				SWAP(list[i], list[j], temp);

			}
		}
	}*/

	merge_sort(list, 0, SIZE - 1);

	printf("\n정렬 후 사전의 내용: \n");
	for (int i = 0; i < SIZE; i++) {
		printf("%s: %s \n", list[i].word, list[i].meaning);

	}
	return 0;

}





