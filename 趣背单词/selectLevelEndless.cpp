#include "selectLevelEndless.h"

void selectLevelEndlessDraw(struct selectLevelEndless* s, struct gameData* gd)
{
	putTransparentImage(NULL, 0, 0, s->bk);
	putTransparentImage(NULL, 701, 45, s->titleImg);

	if (s->isHomeBtnHover == false) {
		s->homeBtn->super.draw((sprite*)s->homeBtn);
	}
	else
	{
		s->bigHomeBtn->super.draw((sprite*)s->bigHomeBtn);
	}
	if (s->isSwitchModeBtnHover == false) {
		s->switchModeBtn->super.draw((sprite*)s->switchModeBtn);
	}
	else
	{
		s->bigSwitchModeBtn->super.draw((sprite*)s->bigSwitchModeBtn);
	}
	for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
		if (s->isLevelBlockBtnHover[i] == false) {
			s->levelBlockBtn[i]->super.draw((sprite*)s->levelBlockBtn[i]);
		}
		else
		{
			s->bigLevelBlockBtn[i]->super.draw((sprite*)s->bigLevelBlockBtn[i]);
		}
	}
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
		for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
			if (BTN_RANGE(s->levelBlockBtn[i])) {
				//后面加别的//目前仅供测试
				switch (i) {
				case 0:s->isQuit = true; gd->isLevelScane = true; gd->difficultyGrade = 1; break;
				case 1:s->isQuit = true; gd->isLevelScane = true; gd->difficultyGrade = 2; break;
				case 2:s->isQuit = true; gd->isLevelScane = true; gd->difficultyGrade = 3; break;
				}
			}
		}
	}

	if (msg->message == WM_MOUSEMOVE) {
		s->isHomeBtnHover = false;
		s->isSwitchModeBtnHover = false;
		for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
			s->isLevelBlockBtnHover[i] = false;
		}

		if (BTN_RANGE(s->homeBtn)) {
			s->isHomeBtnHover = true;
		}
		if (BTN_RANGE(s->switchModeBtn)) {
			s->isSwitchModeBtnHover = true;
		}
		for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
			if (BTN_RANGE(s->levelBlockBtn[i])) {
				s->isLevelBlockBtnHover[i] = true;
			}
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
	loadimage(s->bk, "asset/selectLevelScene/endless/bk.png");
	s->titleImg = new IMAGE;
	loadimage(s->titleImg, "asset/selectLevelScene/endless/title.png");

	s->isQuit = false;
	s->isHomeBtnHover = false;
	s->isSwitchModeBtnHover = false;

	for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
		s->isLevelBlockBtnHover[i] = false;
	}

	s->homeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->homeBtn, 45, 34, 156, 147, "asset/selectLevelScene/endless/homeBtn.png");
	s->bigHomeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigHomeBtn, 38, 27, 170, 161, "asset/selectLevelScene/endless/bigHomeBtn.png");
	s->switchModeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->switchModeBtn, 1218, 47, 110, 110, "asset/selectLevelScene/endless/switchModeBtn.png");
	s->bigSwitchModeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigSwitchModeBtn, 1213, 42, 121, 121, "asset/selectLevelScene/endless/bigSwitchModeBtn.png");

	for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
		s->levelBlockBtn[i] = (struct btn*)malloc(sizeof(struct btn));
		switch (i) {
		case 0:btnInit(s->levelBlockBtn[i], 144, 282, 468, 626, "asset/selectLevelScene/endless/levelBlock1.png"); break;;
		case 1:btnInit(s->levelBlockBtn[i], 708, 282, 470, 627, "asset/selectLevelScene/endless/levelBlock2.png"); break;
		case 2:btnInit(s->levelBlockBtn[i], 1287, 282, 470, 627, "asset/selectLevelScene/endless/levelBlock3.png"); break;
		}
	}
	for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
		s->bigLevelBlockBtn[i] = (struct btn*)malloc(sizeof(struct btn));
		switch (i) {
		case 0:btnInit(s->bigLevelBlockBtn[i], 134, 268, 488, 654, "asset/selectLevelScene/endless/bigLevelBlock1.png"); break;;
		case 1:btnInit(s->bigLevelBlockBtn[i], 698, 269, 490, 653, "asset/selectLevelScene/endless/bigLevelBlock2.png"); break;
		case 2:btnInit(s->bigLevelBlockBtn[i], 1276, 267, 492, 657, "asset/selectLevelScene/endless/bigLevelBlock3.png"); break;
		}
	}
}

void selectLevelEndlessDestroy(struct selectLevelEndless* s)
{
	delete s->bk;
	delete s->titleImg;

	btnDestroy(s->homeBtn);
	free(s->homeBtn);
	btnDestroy(s->bigHomeBtn);
	free(s->bigHomeBtn);
	btnDestroy(s->switchModeBtn);
	free(s->switchModeBtn);
	btnDestroy(s->bigSwitchModeBtn);
	free(s->bigSwitchModeBtn);

	for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
		btnDestroy(s->levelBlockBtn[i]);
		free(s->levelBlockBtn[i]);
	}
	for (int i = 0; i < LEVEL_BLOCK_NUM; i++) {
		btnDestroy(s->bigLevelBlockBtn[i]);
		free(s->bigLevelBlockBtn[i]);
	}
}