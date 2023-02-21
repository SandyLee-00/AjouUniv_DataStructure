// ���� Ž�� Ʈ���� ����� ���� ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE	 100
#define MAX_MEANING_SIZE 200

// ������ ����
typedef struct {
	char word[MAX_WORD_SIZE];		// Ű�ʵ�
	char meaning[MAX_MEANING_SIZE];
} element;
// ����� ����
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
} TreeNode;

// ���� e1 > e2 -> -1 ��ȯ
// ���� e1 == e2 -> 0  ��ȯ 
// ���� e1 < e2 -> 1 ��ȯ
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}
// ���� Ž�� Ʈ�� ��� �Լ�
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
// ���� Ž�� Ʈ�� Ž�� �Լ�
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
	return p; 	// Ž���� �������� ��� NULL ��ȯ
}
// key�� ���� Ž�� Ʈ�� root�� �����Ѵ�. 
// key�� �̹� root�ȿ� ������ ���Ե��� �ʴ´�.

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

// ���� �Լ�
TreeNode* delete_node(TreeNode* root, element key)
{
	if (root == NULL) { 	// Ž��Ʈ���� ���� Ű
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
	printf("i: �Է�");
	printf("d: ����");
	printf("s: Ž��");
	printf("p: ���");
	printf("q: ����");
	printf("x: �κй��ڿ�Ž��");
	printf("**************\n");
}
// ���� Ž�� Ʈ���� ����ϴ� ���� ���� ���α׷� 
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
			printf("�ܾ�:");
			gets(e.word);
			printf("�ǹ�:");
			gets(e.meaning);
			root = insert_node(root, e);
			break;
		case 'd':
			printf("�ܾ�:");
			gets(e.word);
			root = delete_node(root, e);
			break;
		case 'p':
			display(root,1);
			printf("\n");
			break;
		case 's':
			printf("�ܾ�:");
			gets(e.word);
			tmp = search(root, e);
			if (tmp != NULL)
				printf("�ǹ�:%s\n", (tmp->key).meaning);
			break;
		case 'x' :
			printf("���ڿ�:");
			gets(e.word);
			search2(root, e);
			break;
		}

	} while (command != 'q');
}
