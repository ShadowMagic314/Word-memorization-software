#include "menuScene.h"


void menuSceneDraw(struct menuScene* s, struct gameData* gd)
{
	putTransparentImage(NULL, 0, 0, s->bk);
	putTransparentImage(NULL, 584, 130, s->animation[s->animationPlayCnt]);

	s->startBtn->super.draw((sprite*)s->startBtn);
	s->gachaBtn->super.draw((sprite*)s->gachaBtn);
	s->exitBtn->super.draw((sprite*)s->exitBtn);
	if (s->isLongPress == false) {
		if (s->isStartBtnHover == true) {
			putTransparentImage(NULL, 614, 468, s->bigStartBtn);
		}
		if (s->isGachaBtnHover == true) {
			putTransparentImage(NULL, 614, 628, s->bigGachaBtn);
		}
		if (s->isExitBtnHover == true) {
			putTransparentImage(NULL, 614, 785, s->bigExitBtn);
		}
	}

	s->pinBall->super.draw((sprite*)s->pinBall);

	if (gd->isDeveloperMode == true) {
		settextcolor(BLACK);
		settextstyle(140, 0, "微软雅黑");
		setbkmode(TRANSPARENT);
		outtextxy(0, 0, "开发者模式已启用！");
	}
}

void menuSceneUpdate(struct menuScene* s, struct gameData* gd)
{
	s->animationPlayCnt++;
	if (s->animationPlayCnt >= ANIMATIONIMAGENUM ) {
		s->animationPlayCnt = 0;
	}

	if (s->isLongPress == true) {
		s->pinBall->x = s->mouseX;
		s->pinBall->y = s->mouseY;
		
		switch (s->developerModeCnt) {//拖着球从第四象限开始，顺时针走一圈，逆时针走一圈
		case 0:if (RECT_RANGE(s->fourthQuadrant)) s->developerModeCnt++; else s->developerModeCnt = 0; break;
		case 1:if (RECT_RANGE(s->firstQuadrant)) s->developerModeCnt++; else if (RECT_RANGE(s->fourthQuadrant)) {}
			  else s->developerModeCnt = 0; break;
		case 2:if (RECT_RANGE(s->secondQuadrant)) s->developerModeCnt++; else if (RECT_RANGE(s->firstQuadrant)) {}
			  else s->developerModeCnt = 0; break;
		case 3:if (RECT_RANGE(s->thirdQuadrant)) s->developerModeCnt++; else if (RECT_RANGE(s->secondQuadrant)) {}
			  else s->developerModeCnt = 0; break;
		case 4:if (RECT_RANGE(s->fourthQuadrant)) s->developerModeCnt++; else if (RECT_RANGE(s->thirdQuadrant)) {}
			  else s->developerModeCnt = 0; break;
		case 5:if (RECT_RANGE(s->thirdQuadrant)) s->developerModeCnt++; else if (RECT_RANGE(s->fourthQuadrant)) {}
			  else s->developerModeCnt = 0; break;
		case 6:if (RECT_RANGE(s->secondQuadrant)) s->developerModeCnt++; else if (RECT_RANGE(s->thirdQuadrant)) {}
			  else s->developerModeCnt = 0; break;
		case 7:if (RECT_RANGE(s->firstQuadrant)) s->developerModeCnt++; else if (RECT_RANGE(s->secondQuadrant)) {}
			  else s->developerModeCnt = 0; break;
		case 8:if (RECT_RANGE(s->fourthQuadrant)) s->developerModeCnt++; else if (RECT_RANGE(s->firstQuadrant)) {}
			  else s->developerModeCnt = 0; break;
		}
		if (s->developerModeCnt == 9) {
			s->developerModeCnt = -1;
			gd->isDeveloperMode = true;

			//其实这些写在这里不合适，但是目前就是在meunScene里开启开发者模式，所以写这里也没问题
			//有些暂时没用到的数据没有加
			gd->pinkballNum = 999999;
			gd->levelSchedule = 120;
			for (int i = 0; i < gd->characterDB.fiveStarCharacterNum; i++) {
				gd->ownFiveStarCharacters[i] = true;
			}
			for (int i = 0; i < gd->characterDB.fourStarCharacterNum; i++) {
				gd->ownFourStarCharacters[i] = true;
			}
		}
	}
	else {
		s->pinBall->super.update((sprite*)s->pinBall);
	}

	if (s->isLongPressTrigger==true) {
		s->longPressTriggerCnt++;
		if (s->longPressTriggerCnt >= 2) {
			s->isLongPressTrigger = false;
			s->longPressTriggerCnt = 0;
			s->isLongPress = true;
		}
	}
	if (s->isLongPressTrigger == false) {
		s->longPressTriggerCnt = 0;
	}
}

void menuSceneControl(struct menuScene* s, ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_MOUSEMOVE) {
		s->isStartBtnHover = false;
		s->isGachaBtnHover = false;
		s->isExitBtnHover = false;
		if (s->startBtn->super.x < msg->x && msg->x < s->startBtn->super.x + s->startBtn->super.width && s->startBtn->super.y < msg->y && msg->y < s->startBtn->super.y + s->startBtn->super.height)
		{
			s->isStartBtnHover = true;
		}
		if (s->gachaBtn->super.x < msg->x && msg->x < s->gachaBtn->super.x + s->gachaBtn->super.width && s->gachaBtn->super.y < msg->y && msg->y < s->gachaBtn->super.y + s->gachaBtn->super.height)
		{
			s->isGachaBtnHover = true;
		}
		if (s->exitBtn->super.x < msg->x && msg->x < s->exitBtn->super.x + s->exitBtn->super.width && s->exitBtn->super.y < msg->y && msg->y < s->exitBtn->super.y + s->exitBtn->super.height)
		{
			s->isExitBtnHover = true;
		}

		s->mouseX = msg->x;
		s->mouseY = msg->y;
	}

	if (msg->message == WM_LBUTTONDOWN)
	{
		if (s->isLongPress == false) {
			if (s->isStartBtnHover == true) {
				s->isQuit = true;
				gd->isSelectLevelScene = true;
			}
			if (s->isGachaBtnHover == true) {
				gd->isGachaScene = true;
				s->isQuit = true;
			}
			if (s->isExitBtnHover == true) {
				s->isQuit = true;
				gd->isExit = true;
			}
			
			if (pow((msg->x - s->pinBall->x), 2) + pow((msg->y - s->pinBall->y), 2) <= pow(s->pinBall->r, 2)) {
				s->isLongPressTrigger = true;
			}
		}
	}

	if (msg->message == WM_LBUTTONUP)
	{
		s->isLongPressTrigger = false;
		s->isLongPress = false;
		pinBallStateReset(s->pinBall);//这个函数写这里不合适，应该写到update里，但是很麻烦
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

	RECT rectScreen = { 0,0,1920,858 };
	s->pinBall = (struct pinBall*)malloc(sizeof(struct pinBall));
	pinBallInit(s->pinBall,70, rectScreen);

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
	s->bigGachaBtn = new IMAGE;
	s->bigExitBtn = new IMAGE;
	loadimage(s->bigStartBtn, "asset/menuScene/bigStartBtn.png");
	loadimage(s->bigGachaBtn, "asset/menuScene/bigGachaBtn.png");
	loadimage(s->bigExitBtn, "asset/menuScene/bigExitBtn.png");

	s->startBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->startBtn, 622, 474, 667, 139, "asset/menuScene/startBtn.png");
	s->gachaBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->gachaBtn, 622, 636, 667, 139, "asset/menuScene/gachaBtn.png");
	s->exitBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->exitBtn, 622, 797, 667, 139, "asset/menuScene/exitBtn.png");

	s->isQuit = false;
	s->isStartBtnHover = false;
	s->isGachaBtnHover = false;
	s->isExitBtnHover = false;
	s->isLongPress = false;
	s->isLongPressTrigger = false;

	s->animationPlayCnt = 0;
	s->longPressTriggerCnt = 0;
	s->mouseX = 0;
	s->mouseY = 0;
	s->developerModeCnt = 0;

	s->firstQuadrant = { 960,0,1920,540 };
	s->secondQuadrant = { 960,540,1920,1080 };
	s->thirdQuadrant = { 0,540,960,1080 };
	s->fourthQuadrant = { 0,0,960,540 };
}

void menuSceneDestroy(struct menuScene* s)
{
	pinBallDestroy(s->pinBall);
	free(s->pinBall);

	delete s->bk;
	for (int i = 0; i < ANIMATIONIMAGENUM; i++) {
		delete s->animation[i];
	}
	free(s->animation);
	delete s->bigStartBtn;
	delete s->bigGachaBtn;
	delete s->bigExitBtn;

	btnDestroy(s->startBtn);
	free(s->startBtn);
	btnDestroy(s->gachaBtn);
	free(s->gachaBtn);
	btnDestroy(s->exitBtn);
	free(s->exitBtn);
}