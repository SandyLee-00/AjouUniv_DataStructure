/*
���� 13.11 ������
�̼��� 2019/12/04
AVLƮ�� ����
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct avl_node {
	struct avl_node* left_child, * right_child;  /* Subtrees. */
	int data;                   /* Pointer to data. */
};

struct avl_node* root;

// ������ ȸ�� �Լ�
struct avl_node*
	rotate_right(struct avl_node* parent)
{
	struct avl_node* child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}
// ���� ȸ�� �Լ�
struct avl_node*
	rotate_left(struct avl_node* parent)
{
	struct avl_node* child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}
// ������-���� ȸ�� �Լ�
struct avl_node*
	rotate_right_left(struct avl_node* parent)
{
	struct avl_node* child = parent->right_child;
	parent->right_child = rotate_right(child);
	return rotate_left(parent);
}
// ����-������ ȸ�� �Լ�
struct avl_node*
	rotate_left_right(struct avl_node* parent)
{
	struct avl_node* child = parent->left_child;
	parent->left_child = rotate_left(child);
	return rotate_right(parent);
}
// Ʈ���� ���̸� ��ȯ
int get_height(struct avl_node* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left_child),
			get_height(node->right_child));
	return height;
}

// ����� �����μ��� ��ȯ
int get_height_diff(struct avl_node* node)
{
	if (node == NULL) return 0;
	return get_height(node->left_child) - get_height(node->right_child);
}

// Ʈ���� ����Ʈ���� �����
struct avl_node*
	rebalance(struct avl_node** node)
{
	int height_diff = get_height_diff(*node);
	if (height_diff > 1) {
		if (get_height_diff((*node)->left_child) > 0)
			*node = rotate_right(*node);
		else
			*node = rotate_left_right(*node);
	}
	else if (height_diff < -1) {
		if (get_height_diff((*node)->right_child) < 0)
			*node = rotate_left(*node);
		else
			*node = rotate_right_left(*node);
	}
	return *node;
}

// AVL Ʈ���� ���� ����
struct avl_node*
	avl_add(struct avl_node** root, int new_key)
{
	if (*root == NULL) {
		*root = (struct avl_node*)
			malloc(sizeof(struct avl_node));
		if (*root == NULL) {
			fprintf(stderr, "�޸� �Ҵ� ����\n");
			exit(1);
		}
		(*root)->data = new_key;
		(*root)->left_child = (*root)->right_child = NULL;
	}
	else if (new_key < (*root)->data) {
		(*root)->left_child = avl_add(&((*root)->left_child),
			new_key);
		*root = rebalance(root);
	}
	else if (new_key > (*root)->data) {
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);
		(*root) = rebalance(root);
	}
	else {
		fprintf(stderr, "�ߺ��� Ű ����\n");
		exit(1);
	}
	return *root;
}

// AVL Ʈ���� Ž���Լ�
struct avl_node* avl_search(struct avl_node* node, int key)
{
	if (node == NULL) return NULL;
	printf("%d ", node->data);
	if (key == node->data) return node;
	else if (key < node->data)
		return avl_search(node->left_child, key);
	else
		return avl_search(node->right_child, key);
}

void main()
{
	//8,9,10,2,1,5,3,6,4,7,11,12
	avl_add(&root, 8);
	avl_add(&root, 9);
	avl_add(&root, 10);
	avl_add(&root, 2);
	avl_add(&root, 1);
	avl_add(&root, 5);
	avl_add(&root, 3);
	avl_add(&root, 6);
	avl_add(&root, 4);
	avl_add(&root, 7);
	avl_add(&root, 11);
	avl_add(&root, 12);
	avl_search(root, 12);
}