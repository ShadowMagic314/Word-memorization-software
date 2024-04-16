#include "selectLevelEndless.h"

void selectLevelEndlessDraw(struct selectLevelEndless* s, struct gameData* gd)
{
	putTransparentImage(NULL, 0, 0, s->bk);
	putTransparentImage(NULL, 701, 45, s->titleImg);

	s->homeBtn->super.draw((sprite*)s->homeBtn);
	s->switchModeBtn->super.draw((sprite*)s->switchModeBtn);
}

void selectLevelEndlessUpdate(struct selectLevelEndless* s, struct gameData* gd)
{

}

void selectLevelEndlessControl(struct selectLevelEndless* s, ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (BTN_RANGE(s->homeBtn)) {
			s->isQuit = true;
			gd->isMenuScene = true;
		}
		if (BTN_RANGE(s->switchModeBtn)) {
			gd->isSwitchMode = true;
			gd->mode = 1;
		}
	}
}

bool selectLevelEndlessIsQuit(struct selectLevelEndless* s, struct gameData* gd)
{
	return s->isQuit;
}

void selectLevelEndlessInit(struct selectLevelEndless* s)
{
	s->super.draw = (void(*)(struct scene*, struct gameData* gd))selectLevelEndlessDraw;
	s->super.update = (void(*)(struct scene*, struct gameData* gd))selectLevelEndlessUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))selectLevelEndlessControl;
	s->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))selectLevelEndlessIsQuit;

	s->bk = new IMAGE;
	loadimage(s->bk, "asset/selectLevelScene/Endless/bk.png");
	s->titleImg = new IMAGE;
	loadimage(s->titleImg, "asset/selectLevelScene/Endless/title.png");

	s->isQuit = false;

	s->homeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->homeBtn, 45, 34, 156, 147, "asset/selectLevelScene/Endless/homeBtn.png");
	s->switchModeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->switchModeBtn, 1218, 47, 110, 110, "asset/selectLevelScene/Endless/switchModeBtn.png");
}

void selectLevelEndlessDestroy(struct selectLevelEndless* s)
{
	delete s->bk;
	delete s->titleImg;

	btnDestroy(s->homeBtn);
	free(s->homeBtn);
	btnDestroy(s->switchModeBtn);
	free(s->switchModeBtn);
}