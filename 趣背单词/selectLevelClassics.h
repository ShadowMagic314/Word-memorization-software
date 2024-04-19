#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "image.h"
#include "btn.h"
#include <stdio.h>

#define LEVEL_NUM 120//现有关卡总数
#define LEVEL_NUM_EVERY_PAGE 20//每一页关卡数

struct selectLevelClassics {
	struct scene super;

	IMAGE* bk;
	IMAGE* levelBlock;
	IMAGE* bigLevelBlock;
	IMAGE* titleImg;
	IMAGE* voidstar;
	IMAGE* fullstar;

	RECT* rectLevels;//每一个关卡块
	RECT* bigRectLevels;

	int selectedLevel;//按实际来，1开始
	int pageNum;//现在是第几页，1开始
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

	bool isSelectError;//越级选择
};

void selectLevelClassicsInit(struct selectLevelClassics* s);
void selectLevelClassicsDestroy(struct selectLevelClassics* s);