#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define QUESTIONNUMEVERYLEVEL 20
#define FIRSTPASSREWARDS 10//首次通关奖励粉球数
#define REPEATPASSREWARDS 2//重复通关奖励粉球数

#include"scene.h"
#include"gameData.h"
#include "btn.h"
#include <stdlib.h>

struct levelScene {
	struct scene super;

	IMAGE* bkLevel;
	IMAGE* imgBingo;
	IMAGE* imgError;

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

	char words[20][50];
	char chineses[20][100];

	bool isPlayBingoSound;
	bool isPlayErrorSound;

	bool soundFlag[4];//0-A 1-B 3-C 4-D true是还没响过,false是已经响过了
};

void levelSceneInit(struct levelScene* s,struct gameData* gd);
void levelSceneDestroy(struct levelScene* s);