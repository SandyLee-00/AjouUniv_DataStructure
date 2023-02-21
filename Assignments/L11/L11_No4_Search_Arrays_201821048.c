/*
���� 13.2, 4, 5, 6, 7 ������
�̼��� 2019/12/04
����Ž��, ��� ����Ž��, �ݺ� ����Ž��, ����Ž��, ����Ž��
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
//13.1 ����Ž��
{
	int i;
	for (i = low; i <= high; i++)
		if (list[i] == key)
			return i;  // Ž���� �����ϸ� Ű ���� �ε��� ��ȯ 
	return -1;    // Ž���� �����ϸ� -1 ��ȯ 
}


int search_binary(int key, int low, int high)
//13.4 ��ȯ Ž���� �̿��� ����Ž��
{
	int middle;
	if (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])    // Ž�� ����
			return middle;
		else if (key < list[middle]) // ���� �κи���Ʈ Ž�� 
			return search_binary(key, low, middle - 1);
		else                   // ������ �κи���Ʈ Ž�� 
			return search_binary(key, middle + 1, high);
	}
	return -1;        // Ž�� ����
}

int search_binary2(int key, int low, int high)
//�ݺ��� �̿��� ����Ž��
{
	int middle;

	while (low <= high) {       // ���� ���ڵ��� ���� ������
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key > list[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}
	return -1;   // �߰ߵ��� ���� 
}

// INDEX_SIZE�� �ε��� ���̺��� ũ��,n�� ��ü �������� �� 
int search_index(int key)
//13.6 ���� ���� Ž��
{
	int i, low, high;
	// Ű ���� ����Ʈ ���� ���� ���� �ƴϸ� Ž�� ����

	if (key<list[0] || key>list[LIST_SIZE - 1])
		return -1;

	// �ε��� ���̺��� �����Ͽ� �ش�Ű�� ���� ����
	for (i = 0; i < LIST_SIZE; i++)
		if (index_list[i].key <= key &&
			index_list[i + 1].key > key)
			break; 
	if (i == INDEX_SIZE) {  // �ε������̺��� ���̸� 
		low = index_list[i - 1].key;
		high = LIST_SIZE;
	}
	else {
		low = index_list[i].key;
		high = index_list[i + 1].key;
	}
	printf("llow=>%d high=>%d", low, high);
	// ����Ǵ� ������ ���� Ž�� 
	return seq_search(key, low, high);
}

//
int search_interpolation(int key, int n)
//13.7 ����Ž��
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
	if (list[low] == key) return(low);  // Ž������
	else return -1;  // Ž������
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
	
	//5�̸� ���� -1�̸� ����
	printf("seq_search_v : %d\n", list[seq_search_v]);
	printf("search_binary_v : %d\n", list[search_binary_v]);
	printf("search_binary2_v : %d\n", list[search_binary2_v]);
	printf("search_index_v : %d\n", list[search_index_v]);
	printf("search_interpolation_v : %d\n", list[search_interpolation_v]);
}


