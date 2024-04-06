#include "selectLevelScene.h"

void selectLevelSceneDraw(struct selectLevelScene* s, struct gameData* gd)
{
	putTransparentImage(NULL, 0, 0, s->bkSelectLevel);
	putTransparentImage(NULL, 708, 56, s->titleImg);
	
	s->gachaBtn->super.draw((sprite*)s->gachaBtn);
	s->homeBtn->super.draw((sprite*)s->homeBtn);

	//¹Ø¿¨¿éÒÔ¼°ÐÇÐÇ
	settextcolor(WHITE);
	settextstyle(100, 0, "Î¢ÈíÑÅºÚ");
	setbkmode(TRANSPARENT);
	char str[5];
	for (int i = 0; i < LEVEL_NUM; i++) {
		putTransparentImage(NULL, s->rectLevels[i].left, s->rectLevels[i].top, s->levelBlock);

		sprintf(str, "%d", i + 1);
		if (i < 9) {
			outtextxy(s->rectLevels[i].left + 35, s->rectLevels[i].top + 10, str);
		}
		else {
			outtextxy(s->rectLevels[i].left + 13, s->rectLevels[i].top + 10, str);
		}
		
		putTransparentImage(NULL, s->rectLevels[i].left + 4, s->rectLevels[i].top + 112, s->voidstar);
		if (i < gd->levelSchedule) {
			putTransparentImage(NULL, s->rectLevels[i].left + 8, s->rectLevels[i].top + 116, s->fullstar);
		}
	}

	if (s->isGachaBtnHover == true) {
		settextcolor(BLACK);
		settextstyle(100, 0, "Î¢ÈíÑÅºÚ");
		setbkmode(TRANSPARENT);
		outtextxy(1550, 110, "³é¿¨");
	}

	if (s->isSelectError == true && s->selectErrorCnt <= 25) {//ÑÓÊ±ÏÔÊ¾
		s->selectErrorCnt++;

		settextcolor(RED);
		settextstyle(100, 0, "Î¢ÈíÑÅºÚ");
		setbkmode(TRANSPARENT);

		char str[30];
		sprintf(str, "ÇëÏÈÍê³ÉµÚ%d¹Ø", gd->levelSchedule + 1);
		outtextxy(0, 0, str);
		FlushBatchDraw();
	}
	else {
		s->selectErrorCnt = 0;
		s->isSelectError = false;
	}
}

void selectLevelSceneUpdate(struct selectLevelScene* s, struct gameData* gd)
{
	for (int i = 0; i < LEVEL_NUM; i++) {
		if (s->selectedLevel == i + 1) {
			if (s->selectedLevel <= gd->levelSchedule + 1) {
				gd->level = s->selectedLevel;
				gd->isLevelScane = true;
				s->isQuit = true;
				break;
			}
			else {
				s->isSelectError = true;
				s->selectedLevel = -1;
				break;
			}
		}
	}
}

void selectLevelSceneControl(struct selectLevelScene* s, ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		for (int i = 0; i < LEVEL_NUM; i++) {
			if (s->rectLevels[i].left < msg->x && msg->x < s->rectLevels[i].right) {
				if (s->rectLevels[i].top < msg->y && msg->y < s->rectLevels[i].bottom) {
					s->selectedLevel = i + 1;
					break;
				}
			}
		}
		if (s->gachaBtn->super.x < msg->x && msg->x < s->gachaBtn->super.x + s->gachaBtn->super.width && s->gachaBtn->super.y < msg->y && msg->y < s->gachaBtn->super.y + s->gachaBtn->super.height)
		{
			gd->isGachaScene = true;
			s->isQuit = true;
		}
		if (s->homeBtn->super.x < msg->x && msg->x < s->homeBtn->super.x + s->homeBtn->super.width && s->homeBtn->super.y < msg->y && msg->y < s->homeBtn->super.y + s->homeBtn->super.height)
		{
			s->isQuit = true;
			gd->isMenuScene = true;
		}
	}
	if (s->gachaBtn->super.x < msg->x && msg->x < s->gachaBtn->super.x + s->gachaBtn->super.width && s->gachaBtn->super.y < msg->y && msg->y < s->gachaBtn->super.y + s->gachaBtn->super.height)
	{
		s->isGachaBtnHover = true;
	}
	else {
		s->isGachaBtnHover = false;
	}
}

bool selectLevelSceneIsQuit(struct selectLevelScene* s, struct gameData* gd)
{
	return s->isQuit;
}

void selectLevelSceneInit(struct selectLevelScene* s)
{
	s->super.draw = (void(*)(struct scene*, struct gameData* gd))selectLevelSceneDraw;
	s->super.update = (void(*)(struct scene*, struct gameData* gd))selectLevelSceneUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))selectLevelSceneControl;
	s->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))selectLevelSceneIsQuit;

	s->bkSelectLevel = new IMAGE;
	loadimage(s->bkSelectLevel, "asset/image/selectLevelScene/bkSelectLevel.png");
	s->levelBlock = new IMAGE;
	loadimage(s->levelBlock, "asset/image/selectLevelScene/levelBlock.png");
	s->titleImg = new IMAGE;
	loadimage(s->titleImg, "asset/image/selectLevelScene/title.png");
	s->voidstar = new IMAGE;
	loadimage(s->voidstar, "asset/image/selectLevelScene/voidstar.png");
	s->fullstar = new IMAGE;
	loadimage(s->fullstar, "asset/image/selectLevelScene/fullstar.png");

	s->rectLevels = (RECT*)malloc(sizeof(RECT) * LEVEL_NUM);
	if (s->rectLevels == NULL) return;
	s->rectLevels[0] = { 281,213,408,333 };
	s->rectLevels[1] = { 589,213,716,333 };
	s->rectLevels[2] = { 897,213,1024,333 };
	s->rectLevels[3] = { 1205,213,1332,333 };
	s->rectLevels[4] = { 1513,213,1640,333 };
	for (int i = 5; i < LEVEL_NUM; i++) {
		s->rectLevels[i].left = s->rectLevels[i - 5].left;
		s->rectLevels[i].right = s->rectLevels[i - 5].right;
		s->rectLevels[i].top = s->rectLevels[i - 5].top + 201;
		s->rectLevels[i].bottom = s->rectLevels[i - 5].bottom + 201;
	}

	s->selectedLevel = -1;

	s->isQuit = false;

	s->gachaBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->gachaBtn, 1700, 80, 169, 168, "asset/image/gachaBtn.png");
	s->homeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->homeBtn, 40, 497, 181, 634, "asset/image/selectLevelScene/homeBtn.png");

	s->isGachaBtnHover = false;

	s->selectErrorCnt = 0;
}

void selectLevelSceneDestroy(struct selectLevelScene* s)
{
	delete s->bkSelectLevel;
	delete s->levelBlock;
	delete s->titleImg;
	delete s->voidstar;
	delete s->fullstar;

	free(s->rectLevels);

	btnDestroy(s->gachaBtn);
	free(s->gachaBtn);
	btnDestroy(s->homeBtn);
	free(s->homeBtn);
}