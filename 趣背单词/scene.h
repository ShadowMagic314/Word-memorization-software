#pragma once
#include<easyx.h>

struct scene {
	void (*draw)(struct scene*, struct gameData* gd);
	void (*update)(struct scene*, struct gameData* gd);
	void (*control)(struct scene*, ExMessage*, struct gameData* gd);
	bool (*isQuit)(struct scene*, struct gameData* gd);
};