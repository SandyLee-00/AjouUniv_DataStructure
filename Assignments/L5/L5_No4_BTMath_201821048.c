#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode { //285page
	//트리를 사용하기 위한 노드
	int data; //데이터
	struct TreeNode* left, * right; //왼쪽오른쪽 연결
} TreeNode;

//285page
TreeNode n1 = { 1,  NULL, NULL }; //노드 생성
TreeNode n2 = { 4,  NULL,  NULL }; //노드 생성
TreeNode n3 = { '*',  &n1,  &n2 }; //노드 생성
TreeNode n4 = { 16, NULL, NULL }; //노드 생성
TreeNode n5 = { 25, NULL, NULL }; //노드 생성
TreeNode n6 = { '+', &n4,  &n5 }; //노드 생성
TreeNode n7 = { '+', &n3,  &n6 }; //노드 생성
TreeNode* exp = &n7; 

int evaluate(TreeNode* root) //285page
{
	if (root == NULL)
		//루트가 널이면 0을 반환 ex) 8 + a 에 a가 널일 경우 0으로 처리
		return 0;
	if (root->left == NULL && root->right == NULL)
		//리프노드의 왼쪽 오른쪽이 없으면 그 리프노드 데이터 반환
		return root->data;
	else {
		//왼쪽부터 재귀적으로 호출, 포스트 트레버셜을 한다.
		int op1 = evaluate(root->left); //왼쪽 호출
		int op2 = evaluate(root->right); //오른쪽 호출
		printf("%d %c %d를 계산합니다\n", op1, root->data, op2);
		//계산내용 출력 왼쪽 값, 가운데 연산자, 오른쪽 값
		switch (root->data) { //가운데 연산자의 종류에 따라
		case '+': //더하기
			return op1 + op2;
		case '-': //빼기
			return op1 - op2;
		case '*': //곱하기
			return op1 * op2;
		case '/': //나누기
			return op1 / op2;
		}
	}
	return 0;
}
// 
void main() //285page
{
	//트리에 넣은 것 불러 전체 계산하기
	printf("%d", evaluate(exp));
}
