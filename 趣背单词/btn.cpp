#include"btn.h"

void btnDraw(struct btn* b)
{
	putTransparentImage(NULL, b->super.x, b->super.y, b->img);
}

void btnUpdate(struct btn* b)
{

}

void btnInit(struct btn* b, const int x, const int y, const int width, const int height, const char imgPath[20])
{
	b->super.draw = (void (*)(struct sprite*))btnDraw;
	b->super.update = (void (*)(struct sprite*))btnUpdate;

	b->super.x = x;
	b->super.y = y;
	b->super.width = width;
	b->super.height = height;

	b->img = new IMAGE;
	loadimage(b->img, imgPath);
}

void btnDestroy(struct btn* b)
{
	delete b->img;
}