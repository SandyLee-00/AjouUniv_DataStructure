#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode { //���� 287
	//Ʈ���� ����ϱ� ���� ���
	int data; //������
	struct TreeNode* left, * right; //���ʿ����� ����
} TreeNode;

int calc_direc_size(TreeNode* root) //���� 287
{
	int left_size, right_size;
	//���� ������ ����
	if (root == NULL) //���̸� 0��ȯ
		return 0;

	left_size = calc_direc_size(root->left); //���� ȣ��
	right_size = calc_direc_size(root->right); //������ ȣ��
	return (root->data + left_size + right_size); 
	//��Ʈ, ����, ������ ���� �� ��ȯ
}

int main() //���� 287
{
	TreeNode n4 = { 500, NULL, NULL }; //��� ����
	TreeNode n5 = { 200, NULL, NULL }; //��� ����
	TreeNode n3 = { 100, &n4, &n5 }; //��� ����
	TreeNode n2 = { 50, NULL, NULL }; //��� ����
	TreeNode n1 = { 0, &n2, &n3 }; //��� ����
	 
	printf("���丮�� ũ��=%d\n", calc_direc_size(&n1));
	//Ʈ���� ���� �� �ҷ� ��ü ����ϱ�

	return 0;
}
