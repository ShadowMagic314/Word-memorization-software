#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"vector.h"
#include<easyx.h>
#include<stdio.h>
#define FIVE_STAR_CHARACTERNUM 6
#define FOUR_STAR_CHARACTERNUM 5

//��ģ�������Ϊ�洢�⹩���ң���û�з�����ֻ��init��destroy

struct characterDatabase {
	const char* fiveStarCharacterName[FIVE_STAR_CHARACTERNUM] = { "����","��¬��","����","Ī��","����","��", };
	const char* fourStarCharacterName[FOUR_STAR_CHARACTERNUM] = { "����","�ϰ���","ŵ����","����", "���" };

	const int fiveStarCharacterNum = FIVE_STAR_CHARACTERNUM;
	const int fourStarCharacterNum = FOUR_STAR_CHARACTERNUM;

	vector vecFiveStarCharacterImg;
	vector vecFiveStarCharacterMask;
	vector vecFourStarCharacterImg;
	vector vecFourStarCharacterMask;
};

void characterDatabaseInit(struct characterDatabase*cd);
void characterDatabaseDestroy(struct characterDatabase*cd);