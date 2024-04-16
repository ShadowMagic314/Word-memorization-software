#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "btn.h"
#include "pinBall.h"
#include <math.h>
#include <graphics.h>

#define ANIMATIONIMAGENUM 50
#define RECT_RANGE(quadrant) quadrant.left < s->mouseX && s->mouseX < quadrant.right && quadrant.top < s->mouseY && s->mouseY < quadrant.bottom

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
	int developerModeCnt;

	RECT firstQuadrant;
	RECT secondQuadrant;
	RECT thirdQuadrant;
	RECT fourthQuadrant;
};

void menuSceneInit(struct menuScene* s);
void menuSceneDestroy(struct menuScene* s);