/*
[����#8] �迭�� ������ �̿��� ����ó�� ���α׷�
�䱸���� : �� �ǽ� ������ �����ؼ� 5���� �л� ������ �ش��ϴ� ������ ������
0~99�� ���̷� �����ϰ� �̿� ���� �� �׸� ȯ�������� ǥ���ؼ�
�� �л��� ������ ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

������� : ���� ������� �����ο� �������� ��� ������.
(��, ���� ǥ�ô� �Ҽ��� ù°�ڸ�������)
ȭ�鿡 ��µǴ� ���´� ���� ǥ�� ���·� �����ų�
�ƴϸ�, ������ ���ؼ� �߻��Ǵ� ������ 2���� �迭�� ���·� ����� �ǰ�
�л����� ������ ������ ǥ���ص� �˴ϴ�.
�߰� ��� ���� :
1) �ִ밪 �� �ּҰ� ��� �� ǥ��
2)��հ� ǥ��
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define row 8
#define colum 8
#define max 999999

void print_array(double student[][colum]) {

	printf("�й�*****�⼮*****�߰�*****�⸻*****����*****����*****����*****����****\n");
	for (int i = 0; i < row - 3; i++) {
		for (int j = 0; j < colum; j++) {
			if (j == 0 || j == 7) {
				printf("|%7.0lf|", student[i][j]);
			}
			else {
				printf("|%7.1lf|", student[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void set_zero_array(double student[][colum]) {

	for (int i = 0; i < row + 1; i++) {
		student[i][0] = (double)i + 1;
		for (int j = 1; j < colum; j++) {
			student[i][j] = 0;
		}

	}
	print_array(student);
}

void set_random_array(double student[][colum]) {

	for (int i = 0; i < row; i++) {
		for (int j = 1; j < 6; j++) {
			student[i][j] = rand() % 100;
		}
	}
	print_array(student);
}

void weight_get_finalscore(double student[][colum]) {

	double atten = 0.1, mid = 0.2, fin = 0.2;
	double hw = 0.3, atti = 0.2;

	for (int i = 0; i < row; i++) {
		student[i][1] = student[i][1] * atten;
	}
	for (int i = 0; i < row; i++) {
		student[i][2] = student[i][2] * mid;
	}
	for (int i = 0; i < row; i++) {
		student[i][3] = student[i][3] * fin;
	}
	for (int i = 0; i < row; i++) {
		student[i][4] = student[i][4] * hw;
	}
	for (int i = 0; i < row; i++) {
		student[i][5] = student[i][5] * atti;
	}
	for (int i = 0; i < row; i++) {
		double sum = 0;
		for (int j = 1; j < 6; j++) {
			sum = sum + student[i][j];
		}
		student[i][6] = sum;
	}
	print_array(student);
}


void mark_ranking(double student[][colum]) {

	for (int rank = 1; rank < row + 1; rank++) {
		int rank_flag = row;

		for (int i = 0; i < row; i++) {

			if (student[i][6] > student[rank_flag][6] && student[i][7] < 1) {
				rank_flag = i;
			}
		}
		student[rank_flag][7] = rank;
	}

	print_array(student);
}

void sort_ranking() {

}

void minimum() {
	for (int i = 0; i < column; i++)
	{
		student[row][column_sort] = max;
		int flag = row;


		for (int j = 0; j < row; j++) {
			if (student[j][column_sort] < student[flag][column_sort]) {
				flag = j
			}
		}
		printf("min : %lf", student[flag][column_sort]);
	}
}

void maximun() {
	student[row][column_sort] = -1;
	int flag = row;

	for (int j = 0; j < row; j++) {
		if (student[j][column_sort] > student[flag][column_sort]) {
			flag = j
		}
	}
	printf("max : %lf", student[flag][column_sort]);
}

void average() {
	double average = 0;

	for (int j = 0; j < row; j++) {
		average = average + student[j][column_sort]
	}
	printf("average : %lf", student[flag][column_sort]);
}

int main() {
	srand((unsigned)time(NULL));

	double student[row + 1][colum];

	set_zero_array(student);

	set_random_array(student);

	weight_get_finalscore(student);

	mark_ranking(student);

	printf("�ִ� : ");
	printf("�ּڰ� : ");
	printf("��հ� : ");

	return 0;
}
