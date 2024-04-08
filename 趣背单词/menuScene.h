#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "btn.h"

#define ANIMATIONIMAGENUM 50

struct menuScene {
	struct scene super;

	IMAGE* bk;
	IMAGE** animation;
	IMAGE* bigStartBtn;
	IMAGE* bigSettingBtn;
	IMAGE* bigExitBtn;
	
	btn* startBtn;
	btn* settingBtn;
	btn* exitBtn;

	bool isQuit;
	bool isStartBtnHover;
	bool isSettingBtnHover;
	bool isExitBtnHover;

	int animationPlayCnt;
};

void menuSceneInit(struct menuScene* s);
void menuSceneDestroy(struct menuScene* s);