﻿/* 천인국, 공용해, 하상호 지음, C언어로 쉽게 풀어쓴 자료구조(개정3판), 생능출판사. 프로그램 14.1~14.6 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define KEY_SIZE 10 // 탐색키의 최대길이
#define TABLE_SIZE 13 // 해시 테이블의 크기(소수)
typedef struct
{
	char key[KEY_SIZE];
	// 다른 필요한 필드들
} element;
element hash_table[TABLE_SIZE]; // 해싱 테이블
void init_table(element ht[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
		ht[i].key[0] = '/0';
}
int transform(char* key)
{
	int number = 0;
	while (*key)
		number = number + *key++;
	return number;
}
// 제산 함수를 사용한 해싱 함수
int hash_function(char* key)
{
	// 키를 자연수로 변환한 다음 테이블의 크기로
	// 나누어 나머지를 반환
	return transform(key) % TABLE_SIZE;
}

#define empty(item) (strlen(item.key)==0)
#define equal(item1, item2) (!strcmp(item1.key,item2.key))
// 선형 조사법을 이용하여 테이블에 키를 삽입하고,
// 테이블이 가득 찬 경우는 종료
void hash_lp_add(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_function(item.key);
	//printf("hash_address=%d\n", i);
	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "탐색키가 중복되었습니다\n");
			exit(1);
		}
		i = (i + 1) % TABLE_SIZE; // 옆 칸을 살펴봄
		if (i == hash_value) { // 한바퀴 돌아 제자리
			fprintf(stderr, "테이블이 가득찼습니다\n");
			exit(1);
		}
	}
	ht[i] = item;
}

// 선형조사법을 이용하여 테이블에 저장된 키를 탐색
void hash_lp_search(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_function(item.key);
	while (!empty(ht[i]))
	{
		if (equal(item, ht[i])) {
			fprintf(stderr, "탐색 %s: 위치 = %d\n",
				item.key, i);
			return;
		}
		i = (i + 1) % TABLE_SIZE; // 옆 칸을 살펴봄
		if (i == hash_value) { // 한바퀴 돌아 제자리
			fprintf(stderr, "찾는 값이 테이블에 없음\n");
			return;
		}
	}
	fprintf(stderr, "찾는 값이 테이블에 없음\n");
}

// 해싱 테이블의 내용을 출력
void hash_lp_print(element ht[])
{
	int i;
	printf("\n===============================\n");
	for (i = 0; i < TABLE_SIZE; i++)
		printf("[%d] %s\n", i, ht[i].key);
	printf("===============================\n\n");
}
// 해싱 테이블을 사용한 예제
int main(void)
{
	char* s[7] = { "do", "for", "if", "case", "else", "return", "function" };
	element e;
	for (int i = 0; i < 7; i++) {
		strcpy(e.key, s[i]);
		hash_lp_add(e, hash_table);
		hash_lp_print(hash_table);
	}
	for (int i = 0; i < 7; i++) {
		strcpy(e.key, s[i]);
		hash_lp_search(e, hash_table);
	}
	return 0;
}