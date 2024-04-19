#include "selectLevelClassics.h"

void selectLevelClassicsDraw(struct selectLevelClassics* s, struct gameData* gd)
{
	putTransparentImage(NULL, 0, 0, s->bk);
	putTransparentImage(NULL, 701, 45, s->titleImg);
	
	if (s->isHomeBtnHover == false) {
		s->homeBtn->super.draw((sprite*)s->homeBtn);
	}
	else
	{
		s->bigHomeBtn->super.draw((sprite*)s->bigHomeBtn);
	}

	if (s->isPgupBtnHover == false) {
		s->pgupBtn->super.draw((sprite*)s->pgupBtn);
	}
	else
	{
		s->bigPgupBtn->super.draw((sprite*)s->bigPgupBtn);
	}

	if (s->isPgdnBtnHover == false) {
		s->pgdnBtn->super.draw((sprite*)s->pgdnBtn);
	}
	else
	{
		s->bigPgdnBtn->super.draw((sprite*)s->bigPgdnBtn);
	}

	if (s->isSwitchModeBtnHover == false) {
		s->switchModeBtn->super.draw((sprite*)s->switchModeBtn);
	}
	else
	{
		s->bigSwitchModeBtn->super.draw((sprite*)s->bigSwitchModeBtn);
	}

	//¹Ø¿¨¿éÒÔ¼°ÐÇÐÇ
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	char str[5];
	int  levelNumTemp;
	for (int i = 0; i < LEVEL_NUM_EVERY_PAGE; i++) {
		if (s->isRectLevelsHover[i] == false) {
			putTransparentImage(NULL, s->rectLevels[i].left, s->rectLevels[i].top, s->levelBlock);
		}
		else
		{
			putTransparentImage(NULL, s->rectLevels[i].left-4, s->rectLevels[i].top-3, s->bigLevelBlock);
		}
	
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

void selectLevelClassicsUpdate(struct selectLevelClassics* s, struct gameData* gd)
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

void selectLevelClassicsControl(struct selectLevelClassics* s, ExMessage* msg, struct gameData* gd)
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
		if (BTN_RANGE(s->switchModeBtn)) {
			gd->isSwitchMode = true;
			gd->mode = 2;
		}
	}

	if (msg->message == WM_MOUSEMOVE) {
		s->isHomeBtnHover = false;
		s->isPgdnBtnHover = false;
		s->isPgupBtnHover = false;
		s->isSwitchModeBtnHover = false;
		for (int i = 0; i < LEVEL_NUM_EVERY_PAGE; i++) {
			s->isRectLevelsHover[i] = false;
		}

		if (BTN_RANGE(s->homeBtn)) {
			s->isHomeBtnHover = true;
		}
		if (BTN_RANGE(s->pgdnBtn)) {
			s->isPgdnBtnHover = true;
		}
		if (BTN_RANGE(s->pgupBtn)) {
			s->isPgupBtnHover = true;
		}
		if (BTN_RANGE(s->switchModeBtn)) {
			s->isSwitchModeBtnHover = true;
		}
		for (int i = 0; i < LEVEL_NUM_EVERY_PAGE; i++) {
			if (s->rectLevels[i].left < msg->x && msg->x < s->rectLevels[i].right) {
				if (s->rectLevels[i].top < msg->y && msg->y < s->rectLevels[i].bottom) {
					s->isRectLevelsHover[i] = true;
				}
			}
		}
	}
}

bool selectLevelClassicsIsQuit(struct selectLevelClassics* s, struct gameData* gd)
{
	return s->isQuit;
}

void selectLevelClassicsInit(struct selectLevelClassics* s)
{
	s->super.draw = (void(*)(struct scene*, struct gameData* gd))selectLevelClassicsDraw;
	s->super.update = (void(*)(struct scene*, struct gameData* gd))selectLevelClassicsUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))selectLevelClassicsControl;
	s->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))selectLevelClassicsIsQuit;

	s->bk = new IMAGE;
	loadimage(s->bk, "asset/selectLevelScene/classics/bk.png");
	s->levelBlock = new IMAGE;
	loadimage(s->levelBlock, "asset/selectLevelScene/classics/levelBlock.png");
	s->bigLevelBlock = new IMAGE;
	loadimage(s->bigLevelBlock, "asset/selectLevelScene/classics/bigLevelBlock.png");
	s->titleImg = new IMAGE;
	loadimage(s->titleImg, "asset/selectLevelScene/classics/title.png");
	s->voidstar = new IMAGE;
	loadimage(s->voidstar, "asset/selectLevelScene/classics/voidstar.png");
	s->fullstar = new IMAGE;
	loadimage(s->fullstar, "asset/selectLevelScene/classics/fullstar.png");

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

	s->isHomeBtnHover = false;
	s->isPgdnBtnHover = false;
	s->isPgupBtnHover = false;
	s->isSwitchModeBtnHover = false;

	s->homeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->homeBtn, 45, 34, 156, 147, "asset/selectLevelScene/classics/homeBtn.png");
	s->bigHomeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigHomeBtn, 38, 27, 170, 161, "asset/selectLevelScene/classics/bigHomeBtn.png");
	s->pgupBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->pgupBtn, 1734, 401, 113, 229, "asset/selectLevelScene/classics/pgupBtn.png");
	s->bigPgupBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigPgupBtn, 1729, 390, 123, 251, "asset/selectLevelScene/classics/bigPgupBtn.png");
	s->pgdnBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->pgdnBtn, 97, 399, 113, 229, "asset/selectLevelScene/classics/pgdnBtn.png");
	s->bigPgdnBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigPgdnBtn, 91, 391, 123, 251, "asset/selectLevelScene/classics/bigPgdnBtn.png");
	s->switchModeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->switchModeBtn, 1218, 47, 110, 110, "asset/selectLevelScene/classics/switchModeBtn.png");
	s->bigSwitchModeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigSwitchModeBtn, 1213, 42, 121, 121, "asset/selectLevelScene/classics/bigSwitchModeBtn.png");

	for (int i = 0; i < LEVEL_NUM_EVERY_PAGE; i++) {
		s->isRectLevelsHover[i] = false;
	}
}

void selectLevelClassicsDestroy(struct selectLevelClassics* s)
{
	delete s->bk;
	delete s->levelBlock;
	delete s->bigLevelBlock;
	delete s->titleImg;
	delete s->voidstar;
	delete s->fullstar;

	free(s->rectLevels);

	btnDestroy(s->homeBtn);
	free(s->homeBtn);
	btnDestroy(s->bigHomeBtn);
	free(s->bigHomeBtn);
	btnDestroy(s->pgupBtn);
	free(s->pgupBtn);
	btnDestroy(s->bigPgupBtn);
	free(s->bigPgupBtn);
	btnDestroy(s->pgdnBtn);
	free(s->pgdnBtn);
	btnDestroy(s->bigPgdnBtn);
	free(s->bigPgdnBtn);
	btnDestroy(s->switchModeBtn);
	free(s->switchModeBtn);
	btnDestroy(s->bigSwitchModeBtn);
	free(s->bigSwitchModeBtn);
}