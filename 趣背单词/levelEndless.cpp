#include "levelEndless.h"

void levelEndlessDraw(struct levelEndless* s, struct gameData* gd)
{
	putTransparentImage(NULL, 0, 0, s->bk);

	s->backBtn->super.draw((sprite*)s->backBtn);
}

void levelEndlessUpdate(struct levelEndless* s, struct gameData* gd)
{

}

void levelEndlessControl(struct levelEndless* s, ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (BTN_RANGE(s->backBtn))
		{
			s->isQuit = true;
			gd->isSelectLevelScene = true;
		}
	}
}

bool levelEndlessIsQuit(struct levelEndless* s, struct gameData* gd)
{
	return s->isQuit;
}

void levelEndlessInit(struct levelEndless* s)
{
	s->super.draw = (void(*)(struct scene*, struct gameData* gd))levelEndlessDraw;
	s->super.update = (void(*)(struct scene*, struct gameData* gd))levelEndlessUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))levelEndlessControl;
	s->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))levelEndlessIsQuit;

	s->bk = new IMAGE;
	loadimage(s->bk, "asset/levelScene/endless/bk.jpg");

	s->isQuit = false;

	s->backBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->backBtn, 45, 34, 156, 147, "asset/levelScene/endless/backBtn.png");
}

void levelEndlessDestroy(struct levelEndless* s)
{
	delete s->bk;

	btnDestroy(s->backBtn);
	free(s->backBtn);
}