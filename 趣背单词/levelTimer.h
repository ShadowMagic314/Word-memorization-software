#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "image.h"
#include "btn.h"
#include <stdio.h>
#include <time.h>

#define LEVEL_NUM 120//现有关卡总数
#define QUESTION_NUM_EVERY_LEVEL 20

struct levelTimer {
	struct scene super;

	IMAGE* bk;
	IMAGE* imgBingo;
	IMAGE* imgError;
	IMAGE* bkCountdown;

	btn* backBtn;
	btn* optionABtn;
	btn* optionBBtn;
	btn* optionCBtn;
	btn* optionDBtn;
	btn* nextBtn;
	btn* pronunciationBtn;

	RECT rectOptionA, rectOptionB, rectOptionC, rectOptionD;
	RECT rectQuestion;

	bool selectedOption[4];//四个数组元素对应四个选项，false表示没有被选择，true表示被选择

	bool isQuit;
	bool isNext;
	bool isPronounce;
	bool** wordListsFlag;//用于标记哪个单词出现过了//[2][10]==true表示第二关第10个单词出现过了//从1开始

	int correctOption;//1-A 2-B 3-C 4-D

	int randLevel;
	int randIndex;
	int mark;
	int errorAnswerIndex[3];//错误答案位

	char word[50];
	char chinese[100];
	char wrongChinese[3][100];

	bool isPlayBingoSound;
	bool isPlayErrorSound;
	bool isSelectFinish;
	bool isFinish;

	bool soundFlag[4];//0-A 1-B 3-C 4-D true是还没响过,false是已经响过了

	clock_t timingStart;
	clock_t timingNow;
	struct countdown* countdown;
	bool isCountdownUpdate;
};

void levelTimerInit(struct levelTimer* s, struct gameData* gd);
void levelTimerDestroy(struct levelTimer* s);