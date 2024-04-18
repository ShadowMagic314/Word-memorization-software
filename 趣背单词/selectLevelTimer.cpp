#include "selectLevelTimer.h"

void selectLevelTimerDraw(struct selectLevelTimer* s, struct gameData* gd)
{
	putTransparentImage(NULL, 0, 0, s->bk);
	putTransparentImage(NULL, 701, 45, s->titleImg);

	s->homeBtn->super.draw((sprite*)s->homeBtn);
	s->switchModeBtn->super.draw((sprite*)s->switchModeBtn);
	for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
		s->levelBlockBtn[i]->super.draw((sprite*)s->levelBlockBtn[i]);
	}
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
		for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
			if (BTN_RANGE(s->levelBlockBtn[i])) {
				//后面加别的//目前仅供测试
				switch (i) {
				case 0:s->isQuit = true; gd->isLevelScane = true; gd->countdown = { 0,1,0 }; break;
				case 1:s->isQuit = true; gd->isLevelScane = true; gd->countdown = { 0,5,0 }; break;
				case 2:s->isQuit = true; gd->isLevelScane = true; gd->countdown = { 0,15,0 }; break;
				//case 3:s->isQuit = true; gd->isLevelScane = true; break;//自定义后面加
				}
			}
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

	for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
		s->levelBlockBtn[i] = (struct btn*)malloc(sizeof(struct btn));
		switch (i) {
		case 0:btnInit(s->levelBlockBtn[i], 278, 246, 599, 361, "asset/selectLevelScene/timer/levelBlock1.png"); break;
		case 1:btnInit(s->levelBlockBtn[i], 1013, 246, 599, 361, "asset/selectLevelScene/timer/levelBlock2.png"); break;
		case 2:btnInit(s->levelBlockBtn[i], 278, 650, 599, 361, "asset/selectLevelScene/timer/levelBlock3.png"); break;
		case 3:btnInit(s->levelBlockBtn[i], 1013, 650, 599, 361, "asset/selectLevelScene/timer/levelBlock4.png"); break;
		}
	}
}

void selectLevelTimerDestroy(struct selectLevelTimer* s)
{
	delete s->bk;
	delete s->titleImg;

	btnDestroy(s->homeBtn);
	free(s->homeBtn);
	btnDestroy(s->switchModeBtn);
	free(s->switchModeBtn);
	for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
		btnDestroy(s->levelBlockBtn[i]);
		free(s->levelBlockBtn[i]);
	}
}