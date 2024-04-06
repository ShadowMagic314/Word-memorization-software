#pragma once
#include"scene.h"
#include"gameData.h"
#include"btn.h"

struct levelFinishScene {
	struct scene super;

	IMAGE* bk;
	
	btn* backBtn;

	bool isQuit;
};

void levelFinishSceneInit(struct levelFinishScene*);
void levelFinishSceneDestroy(struct levelFinishScene*);