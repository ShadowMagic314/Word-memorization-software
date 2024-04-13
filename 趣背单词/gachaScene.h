#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"scene.h"
#include"btn.h"
#include"video.h"
#include"image.h"
#include"gameData.h"
#include<conio.h>

#define PROBABILITY_INCREASE_MULTIPLE 100//保底增加倍率

struct gachaScene {
	struct scene super;

	IMAGE* bk1;
	IMAGE* bk2;
	IMAGE* bkout;
	IMAGE* pinkball;
	IMAGE* imgExp;

	video* videoSingleToGold;
	video* videoSingleToPurple;
	video* videoSingleToBlue;

	video* videoTenToGold;
	video* videoTenToPurple;

	btn* singleBtn;
	btn* tenBtn;
	btn* closeBtn;
	btn* recordBtn;

	bool isSingleGacha;
	bool isTenGacha;
	bool isQuit;
	bool isRecord;
};

void gachaSceneInit(struct gachaScene* s);
void gachaSceneDestroy(struct gachaScene* s);