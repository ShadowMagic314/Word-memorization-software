#include"levelFinishScene.h"

void levelFinishSceneDraw(struct levelFinishScene* lfs, struct gamedata* gd)
{
	putimage(0, 0, lfs->bk);

	lfs->backBtn->super.draw((struct sprite*)lfs->backBtn);
}

void levelFinishSceneUpdate(struct levelFinishScene* lfs, struct gamedata* gd)
{

}

void levelFinishSceneControl(struct levelFinishScene* lfs, ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_LBUTTONDOWN) {
		if (lfs->backBtn->super.x < msg->x && msg->x < lfs->backBtn->super.x + lfs->backBtn->super.width && lfs->backBtn->super.y < msg->y && msg->y < lfs->backBtn->super.y + lfs->backBtn->super.height)
		{
			lfs->isQuit = true;
			gd->isSelectLevelScene = true;
		}
	}
}

bool levelFinishSceneIsQuit(struct levelFinishScene* lfs, struct gamedata* gd)
{
	return lfs->isQuit;
}

void levelFinishSceneInit(struct levelFinishScene* lfs)
{
	lfs->super.draw = (void(*)(struct scene*, struct gameData* gd))levelFinishSceneDraw;
	lfs->super.update = (void(*)(struct scene*, struct gameData* gd))levelFinishSceneUpdate;
	lfs->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))levelFinishSceneControl;
	lfs->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))levelFinishSceneIsQuit;

	lfs->bk = new IMAGE;
	loadimage(lfs->bk, "asset/image/bkLevelFinish.png");

	lfs->backBtn = (btn*)malloc(sizeof(btn));
	btnInit(lfs->backBtn, 575, 750, 750, 288, "asset/image/backBtn2.png");

	lfs->isQuit = false;
}

void levelFinishSceneDestroy(struct levelFinishScene* lfs)
{
	delete lfs->bk;
	btnDestroy(lfs->backBtn);
	free(lfs->backBtn);
}