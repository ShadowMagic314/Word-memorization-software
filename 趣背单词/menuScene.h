#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "btn.h"
#include "pinBall.h"
#include <math.h>
#include <graphics.h>

#define ANIMATIONIMAGENUM 50

struct menuScene {
	struct scene super;

	struct pinBall* pinBall;

	IMAGE* bk;
	IMAGE** animation;
	IMAGE* bigStartBtn;
	IMAGE* bigGachaBtn;
	IMAGE* bigExitBtn;
	
	btn* startBtn;
	btn* gachaBtn;
	btn* exitBtn;

	bool isQuit;
	bool isStartBtnHover;
	bool isGachaBtnHover;
	bool isExitBtnHover;
	bool isLongPress;
	bool isLongPressTrigger;

	int animationPlayCnt;
	int longPressTriggerCnt;
	int mouseX;
	int mouseY;
};

void menuSceneInit(struct menuScene* s);
void menuSceneDestroy(struct menuScene* s);