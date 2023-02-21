/* õ�α�, ������, �ϻ�ȣ ����, C���� ���� Ǯ� �ڷᱸ��(����3��), �������� ��. ���α׷� 12.6 */
/* õ�α�, ������, �ϻ�ȣ ����, C���� ���� Ǯ� �ڷᱸ��(����3��), �������� ��. ���α׷� 12.11 */

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

element list[SIZE];    /* ����ü �迭 ���� */
element sorted[MAX_SIZE];   // �߰� ������ �ʿ�

/* i�� ���ĵ� ���� ����Ʈ�� ���� �ε���  j�� ���ĵ� ������ ����Ʈ�� ���� �ε���  k�� ���ĵ� ����Ʈ�� ���� �ε��� */
void merge(element list[], int left, int mid, int right) {
	int left_i, mid_j, left_k, l;
	left_i = left;
	mid_j = mid + 1;
	left_k = left;
	/* ���� ���ĵ� list�� �պ� */
	while (left_i <= mid && mid_j <= right) {
		if (strcmp(list[left_i].word, list[mid_j].word) < 0)
			sorted[left_k++] = list[left_i++];
		else   sorted[left_k++] = list[mid_j++];

	}
	if (left_i > mid)
		/* ���� �ִ� ���ڵ��� �ϰ� ���� */
		for (l = mid_j; l <= right; l++)
			sorted[left_k++] = list[l];
	else
		/* ���� �ִ� ���ڵ��� �ϰ� ���� */
		for (l = left_i; l <= mid; l++)
			sorted[left_k++] = list[l];
	/* �迭 sorted[]�� ����Ʈ�� �迭 list[]�� �纹�� */
	for (l = left; l <= right; l++)
		list[l] = sorted[l];

} // 
void merge_sort(element list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		/* ����Ʈ�� �յ� ���� */
		merge_sort(list, left, mid);
		/* �κ� ����Ʈ ���� */
		merge_sort(list, mid + 1, right);
		/* �κ� ����Ʈ ���� */
		merge(list, left, mid, right);
		/* �պ� */

	}

}

int main() {

	printf("5���� �ܾ�� �ǹ̸� �Է��Ͻÿ�\n");

	for (int i = 0; i < SIZE; i++) {
		scanf("%s[^\n]", list[i].word); // ����Ű���� �����ϰ� �޴´�.  
		scanf("%s[^\n]", list[i].meaning);// ����Ű���� �����ϰ� �޴´�. 
	}
	// ���� ���� 
	/*
	for (i = 0; i < SIZE - 1; ++i) {
		for (j = i + 1; j < SIZE; ++j) {
			if (strcmp(list[i].word, list[j].word) > 0) {
				SWAP(list[i], list[j], temp);

			}
		}
	}*/

	merge_sort(list, 0, SIZE - 1);

	printf("\n���� �� ������ ����: \n");
	for (int i = 0; i < SIZE; i++) {
		printf("%s: %s \n", list[i].word, list[i].meaning);

	}
	return 0;

}





