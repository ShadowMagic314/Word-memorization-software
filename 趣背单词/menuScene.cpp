#include "menuScene.h"


void menuSceneDraw(struct menuScene* s, struct gameData* gd)
{
	putTransparentImage(NULL, 0, 0, s->bk);
	putTransparentImage(NULL, 584, 130, s->animation[s->animationPlayCnt]);

	s->startBtn->super.draw((sprite*)s->startBtn);
	if (s->isStartBtnHover == true) {
		putTransparentImage(NULL, 614, 468, s->bigStartBtn);
	}
	s->settingBtn->super.draw((sprite*)s->settingBtn);
	if (s->isSettingBtnHover == true) {
		putTransparentImage(NULL, 614, 628, s->bigSettingBtn);
	}
	s->exitBtn->super.draw((sprite*)s->exitBtn);
	if (s->isExitBtnHover == true) {
		putTransparentImage(NULL, 614, 785, s->bigExitBtn);
	}
}

void menuSceneUpdate(struct menuScene* s, struct gameData* gd)
{
	s->animationPlayCnt++;
	if (s->animationPlayCnt >= ANIMATIONIMAGENUM ) {
		s->animationPlayCnt = 0;
	}
}

void menuSceneControl(struct menuScene* s, ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_MOUSEMOVE) {
		s->isStartBtnHover = false;
		s->isSettingBtnHover = false;
		s->isExitBtnHover = false;
		if (s->startBtn->super.x < msg->x && msg->x < s->startBtn->super.x + s->startBtn->super.width && s->startBtn->super.y < msg->y && msg->y < s->startBtn->super.y + s->startBtn->super.height)
		{
			s->isStartBtnHover = true;
		}
		if (s->settingBtn->super.x < msg->x && msg->x < s->settingBtn->super.x + s->settingBtn->super.width && s->settingBtn->super.y < msg->y && msg->y < s->settingBtn->super.y + s->settingBtn->super.height)
		{
			s->isSettingBtnHover = true;
		}
		if (s->exitBtn->super.x < msg->x && msg->x < s->exitBtn->super.x + s->exitBtn->super.width && s->exitBtn->super.y < msg->y && msg->y < s->exitBtn->super.y + s->exitBtn->super.height)
		{
			s->isExitBtnHover = true;
		}
	}

	if (msg->message == WM_LBUTTONDOWN)
	{
		if (s->isStartBtnHover == true) {
			s->isQuit = true;
			gd->isSelectLevelScene = true;
		}
		if (s->isSettingBtnHover == true) {
			//将来在这里写设置功能
		}
		if (s->isExitBtnHover == true) {
			s->isQuit = true;
			gd->isExit = true;
		}
	}
}

bool menuSceneIsQuit(struct menuScene* s, struct gameData* gd)
{
	return s->isQuit;
}

void menuSceneInit(struct menuScene* s)
{
	s->super.draw = (void(*)(struct scene*, struct gameData* gd))menuSceneDraw;
	s->super.update = (void(*)(struct scene*, struct gameData* gd))menuSceneUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))menuSceneControl;
	s->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))menuSceneIsQuit;

	s->bk = new IMAGE;
	loadimage(s->bk, "asset/menuScene/bk.png");
	s->animation = (IMAGE**)malloc(sizeof(IMAGE*) * ANIMATIONIMAGENUM);
	if (s->animation == NULL) return;
	char imagePath[50];
	for (int i = 0; i < ANIMATIONIMAGENUM; i++) {
		s->animation[i] = new IMAGE;
		sprintf(imagePath, "asset/menuScene/animation/%d.png", i + 1);
		loadimage(s->animation[i], imagePath);
	}
	s->bigStartBtn = new IMAGE;
	s->bigSettingBtn = new IMAGE;
	s->bigExitBtn = new IMAGE;
	loadimage(s->bigStartBtn, "asset/menuScene/bigStartBtn.png");
	loadimage(s->bigSettingBtn, "asset/menuScene/bigSettingBtn.png");
	loadimage(s->bigExitBtn, "asset/menuScene/bigExitBtn.png");

	s->startBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->startBtn, 622, 474, 667, 139, "asset/menuScene/startBtn.png");
	s->settingBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->settingBtn, 622, 636, 667, 139, "asset/menuScene/settingBtn.png");
	s->exitBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->exitBtn, 622, 797, 667, 139, "asset/menuScene/exitBtn.png");

	s->isQuit = false;
	s->isStartBtnHover = false;
	s->isSettingBtnHover = false;
	s->isExitBtnHover = false;

	s->animationPlayCnt = 0;
}

void menuSceneDestroy(struct menuScene* s)
{
	delete s->bk;
	for (int i = 0; i < ANIMATIONIMAGENUM; i++) {
		delete s->animation[i];
	}
	free(s->animation);
	delete s->bigStartBtn;
	delete s->bigSettingBtn;
	delete s->bigExitBtn;

	btnDestroy(s->startBtn);
	free(s->startBtn);
	btnDestroy(s->settingBtn);
	free(s->settingBtn);
	btnDestroy(s->exitBtn);
	free(s->exitBtn);
}