#include "selectLevelScene.h"

void selectLevelSceneDraw(struct selectLevelScene* s, struct gameData* gd)
{
	s->modeScene->draw(s->modeScene,gd);
}

void selectLevelSceneUpdate(struct selectLevelScene* s, struct gameData* gd)
{
	s->modeScene->update(s->modeScene, gd);
	if (gd->isSwitchMode == true) {
		gd->isSwitchMode = false;
		switch (gd->lastMode) {
		case 1:selectLevelClassicsDestroy((struct selectLevelClassics*)s->modeScene); break;
		case 2:selectLevelTimerDestroy((struct selectLevelTimer*)s->modeScene); break;
		case 3:selectLevelEndlessDestroy((struct selectLevelEndless*)s->modeScene); break;
		}
		gd->lastMode = gd->mode;

		switch (gd->mode) {
		case 1:	struct selectLevelClassics* classics;
				classics = (struct selectLevelClassics*)malloc(sizeof(struct selectLevelClassics));
				if (classics == NULL) return;
				s->modeScene = (struct scene*)classics;
				selectLevelClassicsInit((struct selectLevelClassics*)s->modeScene);
				break;
		case 2:	struct selectLevelTimer* timer;
			timer = (struct selectLevelTimer*)malloc(sizeof(struct selectLevelTimer));
			if (timer == NULL) return;
			s->modeScene = (struct scene*)timer;
			selectLevelTimerInit((struct selectLevelTimer*)s->modeScene);
			break;
		case 3:	struct selectLevelEndless* endless;
			endless = (struct selectLevelEndless*)malloc(sizeof(struct selectLevelEndless));
			if (endless == NULL) return;
			s->modeScene = (struct scene*)endless;
			selectLevelEndlessInit((struct selectLevelEndless*)s->modeScene);
			break;
		}
	}
}

void selectLevelSceneControl(struct selectLevelScene* s, ExMessage* msg, struct gameData* gd)
{
	s->modeScene->control(s->modeScene, msg, gd);
}

bool selectLevelSceneIsQuit(struct selectLevelScene* s, struct gameData* gd)
{
	bool ret;
	ret = s->modeScene->isQuit(s->modeScene, gd);
	return ret;
}

void selectLevelSceneInit(struct selectLevelScene* s, struct gameData* gd)
{
	s->super.draw = (void(*)(struct scene*, struct gameData* gd))selectLevelSceneDraw;
	s->super.update = (void(*)(struct scene*, struct gameData* gd))selectLevelSceneUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))selectLevelSceneControl;
	s->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))selectLevelSceneIsQuit;

	switch (gd->mode) {
	case 1:	struct selectLevelClassics* classics;
		classics = (struct selectLevelClassics*)malloc(sizeof(struct selectLevelClassics));
		if (classics == NULL) return;
		s->modeScene = (struct scene*)classics;
		selectLevelClassicsInit((struct selectLevelClassics*)s->modeScene);
		break;
	case 2:	struct selectLevelTimer* timer;
		timer = (struct selectLevelTimer*)malloc(sizeof(struct selectLevelTimer));
		if (timer == NULL) return;
		s->modeScene = (struct scene*)timer;
		selectLevelTimerInit((struct selectLevelTimer*)s->modeScene);
		break;
	case 3:	struct selectLevelEndless* endless;
		endless = (struct selectLevelEndless*)malloc(sizeof(struct selectLevelEndless));
		if (endless == NULL) return;
		s->modeScene = (struct scene*)endless;
		selectLevelEndlessInit((struct selectLevelEndless*)s->modeScene);
		break;
	}
}

void selectLevelSceneDestroy(struct selectLevelScene* s, struct gameData* gd) 
{
	switch (gd->mode) {
	case 1:selectLevelClassicsDestroy((struct selectLevelClassics*)s->modeScene); break;
	case 2:selectLevelTimerDestroy((struct selectLevelTimer*)s->modeScene); break;
	case 3:selectLevelEndlessDestroy((struct selectLevelEndless*)s->modeScene); break;
	}
}