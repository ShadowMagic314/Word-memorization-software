#include"gachaScene.h"

void outGold(struct gachaScene* s, struct gameData* gd)
{
	setbkcolor(BLACK);
	cleardevice();
	FlushBatchDraw();
	Sleep(500);

	int r = rand() % 2;
	if (gd->bigMinimumGuaranteeCnt == 1) {
		r = 0;
	}
	int index = 0;
	if (r == 0) {
		index = 0;
		gd->bigMinimumGuaranteeCnt = 0;
	}
	else if (r == 1) {
		int m = 1;
		int n = gd->characterDB.fiveStarCharacterNum - 1;
		index = rand() % (n - m + 1) + m;//假如有四个角色，这里index就是1、2、3
		gd->bigMinimumGuaranteeCnt++;
	}
	putimage(0, 0, s->bkout);
	putTransparentImage(NULL, 0, 0, (IMAGE*)gd->characterDB.vecFiveStarCharacterMask.get(&gd->characterDB.vecFiveStarCharacterMask, index));
	FlushBatchDraw();
	Sleep(1000);
	putTransparentImage(NULL, 0, 0, (IMAGE*)gd->characterDB.vecFiveStarCharacterImg.get(&gd->characterDB.vecFiveStarCharacterImg, index));

	settextcolor(WHITE);
	settextstyle(100, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	outtextxy(200, 700, gd->characterDB.fiveStarCharacterName[index]);
	FlushBatchDraw();
	Sleep(1000);

	setbkcolor(WHITE);

	gd->ownFiveStarCharacters[index] = true;
	gd->goldMinimumGuaranteeCnt = 0;
}

void outPurple(struct gachaScene* s, struct gameData* gd)
{
	setbkcolor(BLACK);
	cleardevice();
	FlushBatchDraw();
	Sleep(500);

	int m = 0;
	int n = gd->characterDB.fourStarCharacterNum - 1;
	int r = rand() % (n - m + 1) + m;//假如有四个角色，这里r就是0、1、2、3
	putimage(0, 0, s->bkout);
	putTransparentImage(NULL, 0, 0, (IMAGE*)gd->characterDB.vecFourStarCharacterMask.get(&gd->characterDB.vecFourStarCharacterMask, r));
	FlushBatchDraw();
	Sleep(1000);
	putTransparentImage(NULL, 0, 0, (IMAGE*)gd->characterDB.vecFourStarCharacterImg.get(&gd->characterDB.vecFourStarCharacterImg, r));

	settextcolor(WHITE);
	settextstyle(100, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	outtextxy(200, 700, gd->characterDB.fourStarCharacterName[r]);
	FlushBatchDraw(); 
	Sleep(1000);

	setbkcolor(WHITE);

	gd->ownFourStarCharacters[r] = true;
	gd->purpleMinimumGuaranteeCnt = 0;
}

void outBlue(struct gachaScene* s, struct gameData* gd)
{
	setbkcolor(BLACK);
	cleardevice();
	FlushBatchDraw();
	Sleep(500);

	int m = 1;
	int n = 10;
	int r = rand() % (n - m + 1) + m;//经验值从1到10

	putimage(0, 0, s->bkout);
	loadimage(s->imgExp, "asset/gachaScene/exp.png");
	putTransparentImage(NULL, 0, 0, s->imgExp);

	settextcolor(WHITE);
	settextstyle(300, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	char info[50];
	sprintf(info, "%dEXP", r);
	outtextxy(700, 700, info);
	FlushBatchDraw();
	Sleep(1000);

	setbkcolor(WHITE);

	gd->exp += r;
	gd->purpleMinimumGuaranteeCnt++;
	gd->goldMinimumGuaranteeCnt++;
}

void singleGacha(struct gachaScene* s, struct gameData* gd)
{
	if (gd->pinkballNum < 1) return;
	gd->pinkballNum--;

	gd->save(gd);//在这里存一次档，如果用户强制退出就一无所获

	int m = 1, n = 60;
	int r = rand() % (n - m + 1) + m;//1~60
	if (gd->purpleMinimumGuaranteeCnt == 9) {
		r = 2;
	}
	if (gd->goldMinimumGuaranteeCnt >= 50) {
		for (int temp = 1; r != 1 && temp <= (gd->goldMinimumGuaranteeCnt - 50) * PROBABILITY_INCREASE_MULTIPLE; temp++) {
			r = rand() % (n - m + 1) + m;
		}
	}

	if (r==1) {
		s->videoSingleToGold->play(s->videoSingleToGold);
		outGold(s, gd);
	}
	else if (1 < r && r <= 6) {
		s->videoSingleToPurple->play(s->videoSingleToPurple);
		outPurple(s, gd);
	}
	else {
		s->videoSingleToBlue->play(s->videoSingleToBlue);
		outBlue(s, gd);
	}

	gd->gachaTimes++;
}

void tenGacha(struct gachaScene* s, struct gameData* gd)
{
	if (gd->pinkballNum < 10) return;
	gd->pinkballNum -= 10;

	gd->save(gd);//在这里存一次档，如果用户强制退出就一无所获

	int m = 1, n = 6;
	int r1 = rand() % (n - m + 1) + m;//1~6
	if (gd->purpleMinimumGuaranteeCnt == 9) {
		r1 = 2;
	}
	if (gd->goldMinimumGuaranteeCnt >= 50) {
		for (int temp = 1; r1 != 1 && temp <= (gd->goldMinimumGuaranteeCnt-50) * PROBABILITY_INCREASE_MULTIPLE; temp++)r1 = rand() % (n - m + 1) + m;
	}
	if (r1 == 1) {//出金
		s->videoTenToGold->play(s->videoTenToGold);

		int rank[10];
		rank[0] = 1;//Gold
		rank[1] = 2;//Purple
		int flag_goldReduce = 1;
		int flag_purpleReduce = 1;
		for (int i = 2; i < 10; i++) {
			int m = 1, n = 60;
			int r2 = rand() % (n - m + 1) + m;//1~60
			if (r2 == 1) {
				if (flag_goldReduce) {
					flag_goldReduce = 0;
					i--;
					continue;
				}
				rank[i] = 1;
			}
			else if (1 < r2 && r2 <= 6) {
				if (flag_purpleReduce) {
					flag_purpleReduce = 0;
					i--;
					continue;
				}
				rank[i] = 2;
			}
			else {
				rank[i] = 3;
			}
		}

		int temp;
		for (int i = 0; i < 10; i++) {
			int p = 0, q = 9;
			int r3 = rand() % (q - p + 1) + p;
			temp = rank[i];
			rank[i] = rank[r3];
			rank[r3] = temp;
		}

		for (int i = 0; i < 10; i++) {
			switch (rank[i]) {
			case 1:outGold(s, gd); break;
			case 2:outPurple(s, gd); break;
			case 3:outBlue(s, gd); break;
			}
		}
	}
	else {//出紫
		s->videoTenToPurple->play(s->videoTenToPurple);

		int rank[10];
		rank[0] = 2;//Purple
		int flag_purpleReduce = 1;
		for (int i = 1; i < 10; i++) {
			int m = 1, n = 60;
			int r2 = rand() % (n - m + 1) + m;//1~60
			if (1 <= r2 && r2 <= 6) {
				if (flag_purpleReduce) {
					flag_purpleReduce = 0;
					i--;
					continue;
				}
				rank[i] = 2;
			}
			else {
				rank[i] = 3;
			}
		}

		int temp;
		for (int i = 0; i < 10; i++) {
			int p = 0, q = 9;
			int r3 = rand() % (q - p + 1) + p;
			temp = rank[i];
			rank[i] = rank[r3];
			rank[r3] = temp;
		}

		for (int i = 0; i < 10; i++) {
			switch (rank[i]) {
			case 2:outPurple(s, gd); break;
			case 3:outBlue(s, gd); break;
			}
		}
	}
	gd->gachaTimes += 10;
}

void showRecord(struct gachaScene* s, struct gameData* gd)
{
	cleardevice();
	putimage(0, 0, s->bk1);
	settextcolor(BLACK);
	settextstyle(100, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	outtextxy(800, 0, "抽卡记录");
	outtextxy(1300, 0, "(按空格键以退出)");

	char str[100];
	settextstyle(200, 0, "微软雅黑");
	sprintf(str, "一共抽卡%d次", gd->gachaTimes);
	outtextxy(450, 100, str);

	char strTemp[100];
	char strName[100];
	settextstyle(100, 0, "微软雅黑");

	memset(str, 0, sizeof(str));
	outtextxy(100, 300, "抽到的五星角色有:");
	for (int i = 0; i < gd->characterDB.fiveStarCharacterNum; i++) {
		if (gd->ownFiveStarCharacters[i]) {
			sprintf(strName, "%s、", gd->characterDB.fiveStarCharacterName[i]);
			sprintf(strTemp, "%s%s", str, strName);
			strcpy(str, strTemp);
		}
	}
	outtextxy(150, 450, str);

	memset(str, 0, sizeof(str));
	outtextxy(100, 650, "抽到的四星角色有:");
	for (int i = 0; i < gd->characterDB.fourStarCharacterNum; i++) {
		if (gd->ownFourStarCharacters[i]) {
			sprintf(strName, "%s、", gd->characterDB.fourStarCharacterName[i]);
			sprintf(strTemp, "%s%s", str, strName);
			strcpy(str, strTemp);
		}
	}
	outtextxy(150, 800, str);

	memset(str, 0, sizeof(str));
	sprintf(str, "一共获得%d经验", gd->exp);
	outtextxy(100, 950, str);

	FlushBatchDraw();
	char CHAR_FOR_EXIT = _getch();
}

void gachaSceneDraw(struct gachaScene* s, struct gameData* gd)
{
	putimage(0, 0, s->bk1);
	putimage(0, 80, s->bk2);

	s->singleBtn->super.draw((sprite*)s->singleBtn);
	s->tenBtn->super.draw((sprite*)s->tenBtn);
	s->closeBtn->super.draw((sprite*)s->closeBtn);
	s->recordBtn->super.draw((sprite*)s->recordBtn);

	putTransparentImage(NULL, 200, 0, s->pinkball);
	settextcolor(BLUE);
	settextstyle(100, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	char str[10];
	sprintf(str, "x%d", gd->pinkballNum);
	outtextxy(300, 0, str);
}

void gachaSceneUpdate(struct gachaScene* s, struct gameData* gd)
{
	if (s->isSingleGacha == true) {
		s->isSingleGacha = false;
		singleGacha(s, gd);
	}
	if (s->isTenGacha == true) {
		s->isTenGacha = false;
		tenGacha(s, gd);
	}
	if (s->isRecord == true) {
		s->isRecord = false;
		showRecord(s, gd);
	}
}

void gachaSceneControl(struct gachaScene* s, ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_LBUTTONDOWN) {
		if (BTN_RANGE(s->singleBtn)) {
			s->isSingleGacha = true;
		}
		if (BTN_RANGE(s->tenBtn)) {
			s->isTenGacha = true;
		}
		if (BTN_RANGE(s->closeBtn)) {
			s->isQuit = true;
			gd->isMenuScene = true;
		}
		else if (BTN_RANGE(s->recordBtn)) {
			s->isRecord = true;
		}
	}
}

bool gachaSceneIsQuit(struct gachaScene* s, struct gameData* gd)
{
	return s->isQuit;
}

void gachaSceneInit(struct gachaScene* s)
{
	s->super.draw = (void (*)(struct scene*, struct gameData* gd))gachaSceneDraw;
	s->super.update = (void (*)(struct scene*, struct gameData* gd))gachaSceneUpdate;
	s->super.control = (void (*)(struct scene*, ExMessage*, struct gameData* gd))gachaSceneControl;
	s->super.isQuit = (bool (*)(struct scene*, struct gameData* gd))gachaSceneIsQuit;

	s->bk1 = new IMAGE;
	loadimage(s->bk1, "asset/gachaScene/bk1.jpg");
	s->bk2 = new IMAGE;
	loadimage(s->bk2, "asset/gachaScene/bk2.jpg");
	s->bkout = new IMAGE;
	loadimage(s->bkout, "asset/gachaScene/bkout.jpg");
	s->pinkball = new IMAGE;
	loadimage(s->pinkball, "asset/gachaScene/pinkball.png");
	s->imgExp = new IMAGE;
	loadimage(s->imgExp, "asset/gachaScene/imgExp.png");

	s->videoSingleToGold = (struct video*)malloc(sizeof(struct video));
	videoInit(s->videoSingleToGold,"asset/video/singleToGold","asset/sounds/gachaSound.wma",177,30);
	s->videoSingleToPurple = (struct video*)malloc(sizeof(struct video));
	videoInit(s->videoSingleToPurple, "asset/video/singleToPurple", "asset/sounds/gachaSound.wma", 177, 30);
	s->videoSingleToBlue = (struct video*)malloc(sizeof(struct video));
	videoInit(s->videoSingleToBlue, "asset/video/singleToBlue", "asset/sounds/gachaSound.wma", 177, 30);

	s->videoTenToGold = (struct video*)malloc(sizeof(struct video));
	videoInit(s->videoTenToGold, "asset/video/tenToGold", "asset/sounds/gachaSound.wma", 177, 30);
	s->videoTenToPurple = (struct video*)malloc(sizeof(struct video));
	videoInit(s->videoTenToPurple, "asset/video/tenToPurple", "asset/sounds/gachaSound.wma", 177, 30);

	s->singleBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->singleBtn, 50, 900, 532, 117, "asset/gachaScene/singleBtn.png");
	s->tenBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->tenBtn, 1300, 900, 532, 117, "asset/gachaScene/tenBtn.png");
	s->closeBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->closeBtn, 0, 0, 101, 80, "asset/gachaScene/closeBtn.png");
	s->recordBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->recordBtn, 1920 - 187 - 50, 0, 187, 80, "asset/gachaScene/recordBtn.png");

	s->isSingleGacha = false;
	s->isTenGacha = false;
	s->isQuit = false;
	s->isRecord = false;
}

void gachaSceneDestroy(struct gachaScene* s)
{
	delete s->bk1;
	delete s->bk2;
	delete s->bkout;
	delete s->pinkball;
	delete s->imgExp;

	videoDestroy(s->videoSingleToGold);
	free(s->videoSingleToGold);
	videoDestroy(s->videoSingleToPurple);
	free(s->videoSingleToPurple);
	videoDestroy(s->videoSingleToBlue);
	free(s->videoSingleToBlue);

	videoDestroy(s->videoTenToGold);
	free(s->videoTenToGold);
	videoDestroy(s->videoTenToPurple);
	free(s->videoTenToPurple);

	btnDestroy(s->singleBtn);
	free(s->singleBtn);
	btnDestroy(s->tenBtn);
	free(s->tenBtn);
	btnDestroy(s->closeBtn);
	free(s->closeBtn);
	btnDestroy(s->recordBtn);
	free(s->recordBtn);
}