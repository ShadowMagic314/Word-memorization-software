#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define QUESTION_NUM_EVERY_LEVEL 20
#define FIRST_PASS_REWARDS 10//�״�ͨ�ؽ���������
#define REPEAT_PASS_REWARDS 2//�ظ�ͨ�ؽ���������

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

	bool selectedOption[4];//�ĸ�����Ԫ�ض�Ӧ�ĸ�ѡ�false��ʾû�б�ѡ��true��ʾ��ѡ��

	bool isQuit;
	bool isNext;
	bool isSuccess;
	bool isPronounce;

	int correctOption;//1-A 2-B 3-C 4-D

	int questionIndex;//�����ǵڼ�������
	int correctAnswerIndex;//��ȷ��λ
	int errorAnswerIndex[3];//�����λ
	int errorCnt;

	char words[20][50];
	char chineses[20][100];

	bool isPlayBingoSound;
	bool isPlayErrorSound;

	bool soundFlag[4];//0-A 1-B 3-C 4-D true�ǻ�û���,false���Ѿ������
};

void levelClassicsInit(struct levelClassics* s,struct gameData* gd);
void levelClassicsDestroy(struct levelClassics* s);