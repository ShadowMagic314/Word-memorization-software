#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "image.h"
#include "btn.h"
#include <stdio.h>

struct levelEndless {
	struct scene super;

	IMAGE* bk;

	bool isQuit;

	btn* backBtn;
};

void levelEndlessInit(struct levelEndless* s);
void levelEndlessDestroy(struct levelEndless* s);