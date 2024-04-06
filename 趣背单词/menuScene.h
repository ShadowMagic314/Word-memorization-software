#pragma once

#include "scene.h"
#include "gameData.h"
#include "btn.h"

struct menuScene {
	struct scene super;

	IMAGE* bk;
	
	btn* startBtn;
	btn* settingBtn;
	btn* exitBtn;

	bool isQuit;
};

void menuSceneInit(struct menuScene* s);
void menuSceneDestroy(struct menuScene* s);