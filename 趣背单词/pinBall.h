#pragma once

#include"sprite.h"
#include<easyx.h>

struct pinBall {
	struct sprite super;

	int x;
	int y;
	int r;
	int dx;
	int dy;

	IMAGE* imgBall;

	RECT rectBoundary;
};

void pinBallStateReset(struct pinBall* pb);

void pinBallInit(struct pinBall* pb, int r, RECT rectBoundary);
void pinBallDestroy(struct pinBall* pb);