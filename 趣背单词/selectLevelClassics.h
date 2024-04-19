#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "image.h"
#include "btn.h"
#include <stdio.h>

#define LEVEL_NUM 120//���йؿ�����
#define LEVEL_NUM_EVERY_PAGE 20//ÿһҳ�ؿ���

struct selectLevelClassics {
	struct scene super;

	IMAGE* bk;
	IMAGE* levelBlock;
	IMAGE* bigLevelBlock;
	IMAGE* titleImg;
	IMAGE* voidstar;
	IMAGE* fullstar;

	RECT* rectLevels;//ÿһ���ؿ���
	RECT* bigRectLevels;

	int selectedLevel;//��ʵ������1��ʼ
	int pageNum;//�����ǵڼ�ҳ��1��ʼ
	int selectErrorCnt;

	bool isQuit;
	bool isHomeBtnHover;
	bool isPgupBtnHover;
	bool isPgdnBtnHover;
	bool isSwitchModeBtnHover;
	bool isRectLevelsHover[LEVEL_NUM_EVERY_PAGE];

	btn* homeBtn;
	btn* bigHomeBtn;
	btn* pgupBtn;
	btn* bigPgupBtn;
	btn* pgdnBtn;
	btn* bigPgdnBtn;
	btn* switchModeBtn;
	btn* bigSwitchModeBtn;

	bool isSelectError;//Խ��ѡ��
};

void selectLevelClassicsInit(struct selectLevelClassics* s);
void selectLevelClassicsDestroy(struct selectLevelClassics* s);