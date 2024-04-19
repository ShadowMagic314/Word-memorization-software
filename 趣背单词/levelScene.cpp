#include "levelScene.h"

void levelSceneDraw(struct levelScene* s, struct gameData* gd)
{
	s->modeScene->draw(s->modeScene, gd);
}

void levelSceneUpdate(struct levelScene* s, struct gameData* gd)
{
	s->modeScene->update(s->modeScene, gd);
}

void levelSceneControl(struct levelScene* s, ExMessage* msg, struct gameData* gd)
{
	s->modeScene->control(s->modeScene, msg, gd);
}

bool levelSceneIsQuit(struct levelScene* s, struct gameData* gd)
{
	bool ret;
	ret = s->modeScene->isQuit(s->modeScene, gd);
	return ret;
}

void levelSceneInit(struct levelScene* s, struct gameData* gd)
{
	s->super.draw = (void(*)(struct scene*, struct gameData* gd))levelSceneDraw;
	s->super.update = (void(*)(struct scene*, struct gameData* gd))levelSceneUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))levelSceneControl;
	s->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))levelSceneIsQuit;

	switch (gd->mode) {
	case 1:	struct levelClassics* classics;
		classics = (struct levelClassics*)malloc(sizeof(struct levelClassics));
		if (classics == NULL) return;
		s->modeScene = (struct scene*)classics;
		levelClassicsInit((struct levelClassics*)s->modeScene, gd);
		break;
	case 2:	struct levelTimer* timer;
		timer = (struct levelTimer*)malloc(sizeof(struct levelTimer));
		if (timer == NULL) return;
		s->modeScene = (struct scene*)timer;
		levelTimerInit((struct levelTimer*)s->modeScene, gd);
		break;
	case 3:	struct levelEndless* endless;
		endless = (struct levelEndless*)malloc(sizeof(struct levelEndless));
		if (endless == NULL) return;
		s->modeScene = (struct scene*)endless;
		levelEndlessInit((struct levelEndless*)s->modeScene, gd);
		break;
	}
}

void levelSceneDestroy(struct levelScene* s, struct gameData* gd)
{
	switch (gd->mode) {
	case 1:levelClassicsDestroy((struct levelClassics*)s->modeScene); break;
	case 2:levelTimerDestroy((struct levelTimer*)s->modeScene); break;
	case 3:levelEndlessDestroy((struct levelEndless*)s->modeScene); break;
	}
	free(s->modeScene);
}