#include "selectLevelScene.h"

void selectLevelSceneDraw(struct selectLevelScene* s, struct gameData* gd)
{
	putTransparentImage(NULL, 0, 0, s->bkSelectLevel);
	putTransparentImage(NULL, 701, 45, s->titleImg);
	
	s->homeBtn->super.draw((sprite*)s->homeBtn);
	s->pgupBtn->super.draw((sprite*)s->pgupBtn);
	s->pgdnBtn->super.draw((sprite*)s->pgdnBtn);

	//¹Ø¿¨¿éÒÔ¼°ÐÇÐÇ
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	char str[5];
	int  levelNumTemp;
	for (int i = 0; i < LEVEL_NUM_EVERY_PAGE; i++) {
		putTransparentImage(NULL, s->rectLevels[i].left, s->rectLevels[i].top, s->levelBlock);

		levelNumTemp = i + 1 + (s->pageNum - 1) * LEVEL_NUM_EVERY_PAGE;
		sprintf(str, "%d", levelNumTemp);
		if (levelNumTemp < 10) {
			settextstyle(100, 0, "Î¢ÈíÑÅºÚ");
			outtextxy(s->rectLevels[i].left + 35, s->rectLevels[i].top + 10, str);
		}
		else if (levelNumTemp < 100) {
			settextstyle(100, 0, "Î¢ÈíÑÅºÚ");
			outtextxy(s->rectLevels[i].left + 13, s->rectLevels[i].top + 10, str);
		}
		else if (levelNumTemp < 1000) {
			settextstyle(80, 0, "Î¢ÈíÑÅºÚ");
			outtextxy(s->rectLevels[i].left+3, s->rectLevels[i].top + 20, str);
		}
		
		putTransparentImage(NULL, s->rectLevels[i].left + 4, s->rectLevels[i].top + 112, s->voidstar);
		if (levelNumTemp <= gd->levelSchedule) {
			putTransparentImage(NULL, s->rectLevels[i].left + 8, s->rectLevels[i].top + 116, s->fullstar);
		}
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
	if (s->selectedLevel != -1) {
		if (s->selectedLevel <= gd->levelSchedule + 1) {
			gd->level = s->selectedLevel;
			gd->isLevelScane = true;
			s->isQuit = true;
		}
		else {
			s->isSelectError = true;
			s->selectedLevel = -1;
		}
	}
}

void selectLevelSceneControl(struct selectLevelScene* s, ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		for (int i = 0; i < LEVEL_NUM_EVERY_PAGE; i++) {
			if (s->rectLevels[i].left < msg->x && msg->x < s->rectLevels[i].right) {
				if (s->rectLevels[i].top < msg->y && msg->y < s->rectLevels[i].bottom) {
					s->selectedLevel = i + 1 + (s->pageNum - 1) * LEVEL_NUM_EVERY_PAGE;
					break;
				}
			}
		}
		if (BTN_RANGE(s->homeBtn)) {
			s->isQuit = true;
			gd->isMenuScene = true;
		}
		if (BTN_RANGE(s->pgupBtn)) {
			if (s->pageNum < LEVEL_NUM / LEVEL_NUM_EVERY_PAGE) {
				s->pageNum++;
			}
		}
		if (BTN_RANGE(s->pgdnBtn)) {
			if (s->pageNum != 1) {
				s->pageNum--;
			}
		}
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
	loadimage(s->bkSelectLevel, "asset/selectLevelScene/bkSelectLevel.png");
	s->levelBlock = new IMAGE;
	loadimage(s->levelBlock, "asset/selectLevelScene/levelBlock.png");
	s->titleImg = new IMAGE;
	loadimage(s->titleImg, "asset/selectLevelScene/title.png");
	s->voidstar = new IMAGE;
	loadimage(s->voidstar, "asset/selectLevelScene/voidstar.png");
	s->fullstar = new IMAGE;
	loadimage(s->fullstar, "asset/selectLevelScene/fullstar.png");

	s->rectLevels = (RECT*)malloc(sizeof(RECT) * LEVEL_NUM_EVERY_PAGE);
	if (s->rectLevels == NULL) return;
	s->rectLevels[0] = { 281,213,408,333 };
	s->rectLevels[1] = { 589,213,716,333 };
	s->rectLevels[2] = { 897,213,1024,333 };
	s->rectLevels[3] = { 1205,213,1332,333 };
	s->rectLevels[4] = { 1513,213,1640,333 };
	for (int i = 5; i < LEVEL_NUM_EVERY_PAGE; i++) {
		s->rectLevels[i].left = s->rectLevels[i - 5].left;
		s->rectLevels[i].right = s->rectLevels[i - 5].right;
		s->rectLevels[i].top = s->rectLevels[i - 5].top + 201;
		s->rectLevels[i].bottom = s->rectLevels[i - 5].bottom + 201;
	}

	s->selectedLevel = -1;
	s->pageNum = 1;
	s->selectErrorCnt = 0;

	s->isQuit = false;

	s->homeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->homeBtn, 45, 34, 156, 147, "asset/selectLevelScene/homeBtn.png");
	s->pgupBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->pgupBtn, 1706, 386, 140, 251, "asset/selectLevelScene/pgupBtn.png");
	s->pgdnBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->pgdnBtn, 85, 386, 140, 251, "asset/selectLevelScene/pgdnBtn.png");
}

void selectLevelSceneDestroy(struct selectLevelScene* s)
{
	delete s->bkSelectLevel;
	delete s->levelBlock;
	delete s->titleImg;
	delete s->voidstar;
	delete s->fullstar;

	free(s->rectLevels);

	btnDestroy(s->homeBtn);
	free(s->homeBtn);
}