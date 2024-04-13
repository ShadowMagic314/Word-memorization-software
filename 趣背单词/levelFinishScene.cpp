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
		if (BTN_RANGE(lfs->backBtn))
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
	loadimage(lfs->bk, "asset/levelFinishScene/bkLevelFinish.png");

	lfs->backBtn = (btn*)malloc(sizeof(btn));
	btnInit(lfs->backBtn, 575, 750, 750, 288, "asset/levelFinishScene/backBtn.png");

	lfs->isQuit = false;
}

void levelFinishSceneDestroy(struct levelFinishScene* lfs)
{
	delete lfs->bk;
	btnDestroy(lfs->backBtn);
	free(lfs->backBtn);
}