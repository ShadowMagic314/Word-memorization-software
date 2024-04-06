#include "menuScene.h"


void menuSceneDraw(struct menuScene* s, struct gameData* gd)
{
	putTransparentImage(NULL, 0, 0, s->bk);

	s->startBtn->super.draw((sprite*)s->startBtn);
	s->settingBtn->super.draw((sprite*)s->settingBtn);
	s->exitBtn->super.draw((sprite*)s->exitBtn);
}

void menuSceneUpdate(struct menuScene* s, struct gameData* gd)
{

}

void menuSceneControl(struct menuScene* s, ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (s->startBtn->super.x < msg->x && msg->x < s->startBtn->super.x + s->startBtn->super.width && s->startBtn->super.y < msg->y && msg->y < s->startBtn->super.y + s->startBtn->super.height)
		{
			s->isQuit = true;
			gd->isSelectLevelScene = true;
		}
		if (s->settingBtn->super.x < msg->x && msg->x < s->settingBtn->super.x + s->settingBtn->super.width && s->settingBtn->super.y < msg->y && msg->y < s->settingBtn->super.y + s->settingBtn->super.height)
		{
			//将来在这里写设置功能
		}
		if (s->exitBtn->super.x < msg->x && msg->x < s->exitBtn->super.x + s->exitBtn->super.width && s->exitBtn->super.y < msg->y && msg->y < s->exitBtn->super.y + s->exitBtn->super.height)
		{
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

	s->startBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->startBtn, 622, 474, 667, 139, "asset/menuScene/startBtn.png");
	s->settingBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->settingBtn, 622, 636, 667, 139, "asset/menuScene/settingBtn.png");
	s->exitBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->exitBtn, 622, 797, 667, 139, "asset/menuScene/exitBtn.png");

	s->isQuit = false;
}

void menuSceneDestroy(struct menuScene* s)
{
	delete s->bk;

	btnDestroy(s->startBtn);
	free(s->startBtn);
	btnDestroy(s->settingBtn);
	free(s->settingBtn);
	btnDestroy(s->exitBtn);
	free(s->exitBtn);
}