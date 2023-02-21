// 이진 탐색 트리를 사용한 영어 사전

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE	 100
#define MAX_MEANING_SIZE 200

// 데이터 형식
typedef struct {
	char word[MAX_WORD_SIZE];		// 키필드
	char meaning[MAX_MEANING_SIZE];
} element;
// 노드의 구조
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
} TreeNode;

// 만약 e1 > e2 -> -1 반환
// 만약 e1 == e2 -> 0  반환 
// 만약 e1 < e2 -> 1 반환
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}
// 이진 탐색 트리 출력 함수
void display(TreeNode* p, int n)
{
	if (p != NULL) {
		printf("(");
		display(p->left, n + 1);
		printf("[%d]%s:%s", n, (p->key).word, (p->key).meaning);
		display(p->right, n + 1);
		printf(")");
	}
}
// 이진 탐색 트리 탐색 함수
TreeNode* search(TreeNode* root, element key)
{
	TreeNode* p = root;
	while (p != NULL) {
		if (compare(key, p->key) == 0)
			return p;
		else if (compare(key, p->key) < 0)
			p = p->left;
		else if (compare(key, p->key) > 0)
			p = p->right;
	}
	return p; 	// 탐색에 실패했을 경우 NULL 반환
}
// key를 이진 탐색 트리 root에 삽입한다. 
// key가 이미 root안에 있으면 삽입되지 않는다.

TreeNode* new_node(element item) {

	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, element key)
{
	if (node == NULL) return new_node(key);
	if (compare(key, node->key) < 0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node->key) > 0)
		node->right = insert_node(node->right, key);
	return node;
}

TreeNode* min_value_node(TreeNode* node) {
	TreeNode* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

// 삭제 함수
TreeNode* delete_node(TreeNode* root, element key)
{
	if (root == NULL) { 	// 탐색트리에 없는 키
		printf("key is not in the tree");
		return root;
	}
	if (compare(key, root->key) < 0)
		root->left = delete_node(root->left, key);
	else if (compare(key, root->key) > 0)
		root->right = delete_node(root->right, key);
	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		TreeNode* temp = min_value_node(root->right);
		root->key = temp->key;
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

void search2(TreeNode* p, element key)
{
	if (p != NULL) {
		search2(p->left, key);
		if (strstr(p->key.word, key.word) != NULL)
			printf(" % s % s\n", p->key.word, p->key.meaning);
		search2(p->right, key);
	}
}

void help()
{
	printf("**************\n");
	printf("i: 입력");
	printf("d: 삭제");
	printf("s: 탐색");
	printf("p: 출력");
	printf("q: 종료");
	printf("x: 부분문자열탐색");
	printf("**************\n");
}
// 이진 탐색 트리를 사용하는 영어 사전 프로그램 
void main()
{
	char command;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp;

	do {
		help();
		command = getchar();
		getchar();
		switch (command) {
		case 'i':
			printf("단어:");
			gets(e.word);
			printf("의미:");
			gets(e.meaning);
			root = insert_node(root, e);
			break;
		case 'd':
			printf("단어:");
			gets(e.word);
			root = delete_node(root, e);
			break;
		case 'p':
			display(root,1);
			printf("\n");
			break;
		case 's':
			printf("단어:");
			gets(e.word);
			tmp = search(root, e);
			if (tmp != NULL)
				printf("의미:%s\n", (tmp->key).meaning);
			break;
		case 'x' :
			printf("문자열:");
			gets(e.word);
			search2(root, e);
			break;
		}

	} while (command != 'q');
}
