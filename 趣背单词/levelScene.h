#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include"scene.h"
#include"gameData.h"
#include "btn.h"
#include "levelClassics.h"
#include "levelTimer.h"
#include "levelEndless.h"

struct levelScene {
	struct scene super;

	struct scene* modeScene;
};

void levelSceneInit(struct levelScene* s, struct gameData* gd);
void levelSceneDestroy(struct levelScene* s, struct gameData* gd);