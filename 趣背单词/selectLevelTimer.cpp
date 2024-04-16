#include "selectLevelTimer.h"

void selectLevelTimerDraw(struct selectLevelTimer* s, struct gameData* gd)
{
	putTransparentImage(NULL, 0, 0, s->bk);
	putTransparentImage(NULL, 701, 45, s->titleImg);

	s->homeBtn->super.draw((sprite*)s->homeBtn);
	s->switchModeBtn->super.draw((sprite*)s->switchModeBtn);
}

void selectLevelTimerUpdate(struct selectLevelTimer* s, struct gameData* gd)
{

}

void selectLevelTimerControl(struct selectLevelTimer* s, ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (BTN_RANGE(s->homeBtn)) {
			s->isQuit = true;
			gd->isMenuScene = true;
		}
		if (BTN_RANGE(s->switchModeBtn)) {
			gd->isSwitchMode = true;
			gd->mode = 3;
		}
	}
}

bool selectLevelTimerIsQuit(struct selectLevelTimer* s, struct gameData* gd)
{
	return s->isQuit;
}

void selectLevelTimerInit(struct selectLevelTimer* s)
{
	s->super.draw = (void(*)(struct scene*, struct gameData* gd))selectLevelTimerDraw;
	s->super.update = (void(*)(struct scene*, struct gameData* gd))selectLevelTimerUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))selectLevelTimerControl;
	s->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))selectLevelTimerIsQuit;

	s->bk = new IMAGE;
	loadimage(s->bk, "asset/selectLevelScene/timer/bk.png");
	s->titleImg = new IMAGE;
	loadimage(s->titleImg, "asset/selectLevelScene/timer/title.png");

	s->isQuit = false;

	s->homeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->homeBtn, 45, 34, 156, 147, "asset/selectLevelScene/timer/homeBtn.png");
	s->switchModeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->switchModeBtn, 1218, 47, 110, 110, "asset/selectLevelScene/timer/switchModeBtn.png");
}

void selectLevelTimerDestroy(struct selectLevelTimer* s)
{
	delete s->bk;
	delete s->titleImg;

	btnDestroy(s->homeBtn);
	free(s->homeBtn);
	btnDestroy(s->switchModeBtn);
	free(s->switchModeBtn);
}