#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<easyx.h>
#include<time.h>
#include"gachaScene.h"
#include"gameData.h"
#include"gameloop.h"
#include"levelScene.h"
#include"selectLevelScene.h"
#include"levelFinishScene.h"
#include"menuScene.h"

int main()
{
	srand((unsigned int)time(NULL));
	initgraph(1920, 1080);
	setbkcolor(WHITE);
	cleardevice();
	//start here
	struct gameData gamedata;
	gameDataInit(&gamedata);
	gamedata.load(&gamedata);

	while (1) {
		if (gamedata.isMenuScene == true) {
			gamedata.isMenuScene = false;

			struct menuScene menuscene;
			menuSceneInit(&menuscene);
			gameLoop((scene*)&menuscene, 25, &gamedata);
			menuSceneDestroy(&menuscene);
		}

		if (gamedata.isSelectLevelScene == true) {
			gamedata.isSelectLevelScene = false;

			struct selectLevelScene selectlevelscene;
			selectLevelSceneInit(&selectlevelscene);
			gameLoop((scene*)&selectlevelscene, 30, &gamedata);
			selectLevelSceneDestroy(&selectlevelscene);
		}

		if (gamedata.isLevelScane == true) {
			gamedata.isLevelScane = false;

			struct levelScene levelscene;
			levelSceneInit(&levelscene, &gamedata);
			gameLoop((scene*)&levelscene, 30, &gamedata);
			levelSceneDestroy(&levelscene);
		}

		if (gamedata.isGachaScene == true) {
			gamedata.isGachaScene = false;

			struct gachaScene gachascene;
			gachaSceneInit(&gachascene);
			gameLoop((scene*)&gachascene, 30, &gamedata);
			gachaSceneDestroy(&gachascene);
		}

		if (gamedata.isLevelFinishScene == true) {
			gamedata.isLevelFinishScene = false;

			struct levelFinishScene levelfinishscene;
			levelFinishSceneInit(&levelfinishscene);
			gameLoop((scene*)&levelfinishscene, 30, &gamedata);
			levelFinishSceneDestroy(&levelfinishscene);
		}

		if (gamedata.isExit == true) {
			break;
		}
	}
	
	gamedata.save(&gamedata);
	gameDataDestroy(&gamedata);
	//end
	closegraph();
	return 0;
}