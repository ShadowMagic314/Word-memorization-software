#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "image.h"
#include "btn.h"
#include <stdio.h>

#define LEVEL_BLOCK_NUM 3

struct selectLevelEndless {
	struct scene super;

	IMAGE* bk;
	IMAGE* titleImg;

	bool isQuit;
	bool isHomeBtnHover;
	bool isSwitchModeBtnHover;
	bool isLevelBlockBtnHover[LEVEL_BLOCK_NUM];

	btn* homeBtn;
	btn* bigHomeBtn;
	btn* switchModeBtn;
	btn* bigSwitchModeBtn;
	btn* levelBlockBtn[LEVEL_BLOCK_NUM];
	btn* bigLevelBlockBtn[LEVEL_BLOCK_NUM];
};

void selectLevelEndlessInit(struct selectLevelEndless* s);
void selectLevelEndlessDestroy(struct selectLevelEndless* s);