#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define QUESTION_NUM_EVERY_LEVEL 20
#define FIRST_PASS_REWARDS 10//首次通关奖励粉球数
#define REPEAT_PASS_REWARDS 2//重复通关奖励粉球数

#include <stdlib.h>
#include"scene.h"
#include"gameData.h"
#include "btn.h"

struct levelClassics {
	struct scene super;

	IMAGE* bk;
	IMAGE* imgBingo;
	IMAGE* imgError;
	IMAGE* threeHearts;
	IMAGE* twoHearts;
	IMAGE* oneHearts;
	IMAGE* zeroHearts;
	IMAGE* badend;

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
	bool isSuccess;
	bool isPronounce;

	int correctOption;//1-A 2-B 3-C 4-D

	int questionIndex;//现在是第几个问题
	int correctAnswerIndex;//正确答案位
	int errorAnswerIndex[3];//错误答案位
	int errorCnt;

	char words[20][50];
	char chineses[20][100];

	bool isPlayBingoSound;
	bool isPlayErrorSound;

	bool soundFlag[4];//0-A 1-B 3-C 4-D true是还没响过,false是已经响过了
};

void levelClassicsInit(struct levelClassics* s,struct gameData* gd);
void levelClassicsDestroy(struct levelClassics* s);