#pragma once
#include"sprite.h"
#include<easyx.h>
#include"image.h"

#define BTN_RANGE(btn) btn->super.x < msg->x && msg->x < btn->super.x + btn->super.width && btn->super.y < msg->y && msg->y < btn->super.y + btn->super.height

struct btn {
	struct sprite super;

	IMAGE* img;
};

void btnInit(struct btn* b, const int x, const int y, const int width, const int height, const char imgPath[20]);
void btnDestroy(struct btn* b);