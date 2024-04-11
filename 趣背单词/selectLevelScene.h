#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "image.h"
#include "btn.h"
#include <stdio.h>

#define LEVEL_NUM 120//现有关卡总数
#define LEVEL_NUM_EVERY_PAGE 20//每一页关卡数

struct selectLevelScene {
	struct scene super;

	IMAGE* bkSelectLevel;
	IMAGE* levelBlock;
	IMAGE* titleImg;
	IMAGE* voidstar;
	IMAGE* fullstar;

	RECT* rectLevels;//每一个关卡块

	int selectedLevel;//按实际来，1开始
	int pageNum;//现在是第几页，1开始
	int selectErrorCnt;

	bool isQuit;

	btn* homeBtn;
	btn* pgupBtn;
	btn* pgdnBtn;

	bool isSelectError;//越级选择
};

void selectLevelSceneInit(struct selectLevelScene* s);
void selectLevelSceneDestroy(struct selectLevelScene* s);