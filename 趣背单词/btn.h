#pragma once
#include"sprite.h"
#include<easyx.h>
#include"image.h"

struct btn {
	struct sprite super;

	IMAGE* img;
};

void btnInit(struct btn* b, const int x, const int y, const int width, const int height, const char imgPath[20]);
void btnDestroy(struct btn* b);