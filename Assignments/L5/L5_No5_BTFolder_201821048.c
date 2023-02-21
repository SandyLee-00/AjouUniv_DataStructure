#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode { //교재 287
	//트리를 사용하기 위한 노드
	int data; //데이터
	struct TreeNode* left, * right; //왼쪽오른쪽 연결
} TreeNode;

int calc_direc_size(TreeNode* root) //교재 287
{
	int left_size, right_size;
	//왼쪽 오른쪽 저장
	if (root == NULL) //널이면 0반환
		return 0;

	left_size = calc_direc_size(root->left); //왼쪽 호출
	right_size = calc_direc_size(root->right); //오른쪽 호출
	return (root->data + left_size + right_size); 
	//루트, 왼쪽, 오른쪽 더한 값 반환
}

int main() //교재 287
{
	TreeNode n4 = { 500, NULL, NULL }; //노드 생성
	TreeNode n5 = { 200, NULL, NULL }; //노드 생성
	TreeNode n3 = { 100, &n4, &n5 }; //노드 생성
	TreeNode n2 = { 50, NULL, NULL }; //노드 생성
	TreeNode n1 = { 0, &n2, &n3 }; //노드 생성
	 
	printf("디렉토리의 크기=%d\n", calc_direc_size(&n1));
	//트리에 넣은 것 불러 전체 계산하기

	return 0;
}
