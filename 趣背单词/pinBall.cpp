#include"pinBall.h"
#include"image.h"
#include"menuScene.h"

void pinBallDraw(struct pinBall* pb, struct menuScene* ms)
{
	if (ms->isPinBallHover == false) {
		putTransparentImage(NULL, pb->x - pb->r, pb->y - pb->r, pb->imgBall);
	}
	else {
		putTransparentImage(NULL, pb->x - pb->r, pb->y - pb->r, pb->imgBigBall);
	}
}

void pinBallUpdate(struct pinBall* pb)
{
	pb->x += pb->dx;
	pb->y += pb->dy;

	if ((pb->x <= pb->rectBoundary.left + pb->r) || (pb->x >= pb->rectBoundary.right - pb->r)) {
		pb->dx = -pb->dx;
	}
	if (pb->y <= pb->rectBoundary.top + pb->r) {
		pb->dy = -pb->dy;
	}
	if (pb->y >= pb->rectBoundary.bottom - pb->r) {
		if (pb->dy <= 3) {
			int m, n;
			m = -50;
			n = -5;
			pb->dy = rand() % (n - m + 1) + m;
		}
		else {
			pb->dy = -pb->dy;
		}
	}

	int m, n;
	m = 0;
	n = 3;
	pb->dy += rand() % (n - m + 1) + m;
}

void pinBallStateReset(struct pinBall* pb)
{
	int m, n;
	m = -3;
	n = 3;
	do {
		pb->dx = rand() % (n - m + 1) + m;
	} while (pb->dx == 0);
	pb->dy = rand() % (n - m + 1) + m;
}

void pinBallInit(struct pinBall* pb, int r, RECT rectBoundary)
{
	pb->super.draw = (void (*)(struct sprite*))pinBallDraw;
	pb->super.update = (void (*)(struct sprite*))pinBallUpdate;

	pb->r = r;

	pb->rectBoundary = rectBoundary;

	int m, n;
	m = rectBoundary.left + r;
	n = rectBoundary.right - r;
	pb->x = rand() % (n - m + 1) + m;
	m = rectBoundary.top + r;
	n = rectBoundary.bottom - r;
	pb->y = rand() % (n - m + 1) + m;

	pinBallStateReset(pb);

	pb->imgBall = new IMAGE;
	loadimage(pb->imgBall, "asset/menuScene/pinBall.png");
	pb->imgBigBall = new IMAGE;
	loadimage(pb->imgBigBall, "asset/menuScene/bigPinBall.png");
}

void pinBallDestroy(struct pinBall* pb)
{
	delete pb->imgBall;
	delete pb->imgBigBall;
}