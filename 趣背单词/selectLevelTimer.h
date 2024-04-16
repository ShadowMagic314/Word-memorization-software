#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "image.h"
#include "btn.h"
#include <stdio.h>

struct selectLevelTimer {
	struct scene super;

	IMAGE* bk;
	IMAGE* titleImg;

	bool isQuit;

	btn* homeBtn;
	btn* switchModeBtn;
};

void selectLevelTimerInit(struct selectLevelTimer* s);
void selectLevelTimerDestroy(struct selectLevelTimer* s);