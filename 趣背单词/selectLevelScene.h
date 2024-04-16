#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "image.h"
#include "btn.h"
#include "selectLevelClassics.h"
#include "selectLevelTimer.h"
#include "selectLevelEndless.h"
#include <stdio.h>

struct selectLevelScene {
	struct scene super;

	struct scene* modeScene;
};

void selectLevelSceneInit(struct selectLevelScene* s, struct gameData* gd);
void selectLevelSceneDestroy(struct selectLevelScene* s, struct gameData* gd);