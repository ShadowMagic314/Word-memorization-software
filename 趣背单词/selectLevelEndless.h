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

	btn* homeBtn;
	btn* switchModeBtn;
	btn* levelBlockBtn[LEVEL_BLOCK_NUM];
};

void selectLevelEndlessInit(struct selectLevelEndless* s);
void selectLevelEndlessDestroy(struct selectLevelEndless* s);