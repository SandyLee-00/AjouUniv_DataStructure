#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode { //285page
	//Ʈ���� ����ϱ� ���� ���
	int data; //������
	struct TreeNode* left, * right; //���ʿ����� ����
} TreeNode;

//285page
TreeNode n1 = { 1,  NULL, NULL }; //��� ����
TreeNode n2 = { 4,  NULL,  NULL }; //��� ����
TreeNode n3 = { '*',  &n1,  &n2 }; //��� ����
TreeNode n4 = { 16, NULL, NULL }; //��� ����
TreeNode n5 = { 25, NULL, NULL }; //��� ����
TreeNode n6 = { '+', &n4,  &n5 }; //��� ����
TreeNode n7 = { '+', &n3,  &n6 }; //��� ����
TreeNode* exp = &n7; 

int evaluate(TreeNode* root) //285page
{
	if (root == NULL)
		//��Ʈ�� ���̸� 0�� ��ȯ ex) 8 + a �� a�� ���� ��� 0���� ó��
		return 0;
	if (root->left == NULL && root->right == NULL)
		//��������� ���� �������� ������ �� ������� ������ ��ȯ
		return root->data;
	else {
		//���ʺ��� ��������� ȣ��, ����Ʈ Ʈ�������� �Ѵ�.
		int op1 = evaluate(root->left); //���� ȣ��
		int op2 = evaluate(root->right); //������ ȣ��
		printf("%d %c %d�� ����մϴ�\n", op1, root->data, op2);
		//��곻�� ��� ���� ��, ��� ������, ������ ��
		switch (root->data) { //��� �������� ������ ����
		case '+': //���ϱ�
			return op1 + op2;
		case '-': //����
			return op1 - op2;
		case '*': //���ϱ�
			return op1 * op2;
		case '/': //������
			return op1 / op2;
		}
	}
	return 0;
}
// 
void main() //285page
{
	//Ʈ���� ���� �� �ҷ� ��ü ����ϱ�
	printf("%d", evaluate(exp));
}
