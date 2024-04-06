#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"vector.h"
#include<easyx.h>
#include<stdio.h>
#define FIVESTARCHARACTERNUM 6
#define FOURSTARCHARACTERNUM 5

//该模块仅仅作为存储库供查找，故没有方法，只有init和destroy

struct characterDatabase {
	const char* fiveStarCharacterName[FIVESTARCHARACTERNUM] = { "钟离","迪卢克","刻晴","莫娜","七七","琴", };
	const char* fourStarCharacterName[FOURSTARCHARACTERNUM] = { "安柏","迪奥娜","诺艾尔","香菱", "烟绯" };

	const int fiveStarCharacterNum = FIVESTARCHARACTERNUM;
	const int fourStarCharacterNum = FOURSTARCHARACTERNUM;

	vector vecFiveStarCharacterImg;
	vector vecFiveStarCharacterMask;
	vector vecFourStarCharacterImg;
	vector vecFourStarCharacterMask;
};

void characterDatabaseInit(struct characterDatabase*cd);
void characterDatabaseDestroy(struct characterDatabase*cd);