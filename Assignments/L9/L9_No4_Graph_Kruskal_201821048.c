/*
[과제#8] 배열과 정렬을 이용한 성적처리 프로그램
요구사항 : 위 실습 내용을 참고해서 5명의 학생 점수에 해당하는 임의의 점수를
0~99점 사이로 생성하고 이에 대한 각 항목별 환산점수로 표시해서
각 학생별 총점과 순위를 구하는 프로그램을 작성하시오.

출력형태 : 각자 나름대로 자유로운 형식으로 출력 가능함.
(단, 점수 표시는 소수점 첫째자리까지만)
화면에 출력되는 형태는 위의 표의 형태로 나오거나
아니면, 난수에 의해서 발생되는 점수만 2차원 배열의 형태로 출력이 되고
학생별로 총점과 순위를 표시해도 됩니다.
추가 기능 구현 :
1) 최대값 및 최소값 계산 및 표시
2)평균값 표시
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define row 8
#define colum 8
#define max 999999

void print_array(double student[][colum]) {

	printf("학번*****출석*****중간*****기말*****과제*****수시*****총점*****순위****\n");
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

	printf("최댓값 : ");
	printf("최솟값 : ");
	printf("평균값 : ");

	return 0;
}
