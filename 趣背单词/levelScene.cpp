#include "levelScene.h"

void levelSceneDraw(struct levelScene* s, struct gameData* gd)
{
	putimage(0, 0, s->bkLevel);

	s->backBtn->super.draw((sprite*)s->backBtn);
	s->optionABtn->super.draw((sprite*)s->optionABtn);
	s->optionBBtn->super.draw((sprite*)s->optionBBtn);
	s->optionCBtn->super.draw((sprite*)s->optionCBtn);
	s->optionDBtn->super.draw((sprite*)s->optionDBtn);
	s->pronunciationBtn->super.draw((sprite*)s->pronunciationBtn);

	settextcolor(BLACK);
	settextstyle(140, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	drawtext(s->words[s->questionIndex], &s->rectQuestion, DT_CENTER);

	settextcolor(BLACK);
	settextstyle(50, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	//打印正确选项
	switch (s->correctOption) {
	case 1:drawtext(s->chineses[s->correctAnswerIndex], &s->rectOptionA, DT_WORDBREAK); break;
	case 2:drawtext(s->chineses[s->correctAnswerIndex], &s->rectOptionB, DT_WORDBREAK); break;
	case 3:drawtext(s->chineses[s->correctAnswerIndex], &s->rectOptionC, DT_WORDBREAK); break;
	case 4:drawtext(s->chineses[s->correctAnswerIndex], &s->rectOptionD, DT_WORDBREAK); break;
	}
	
	//打印错误选项
	int j = 0;//遍历三个错误答案
	for (int i = 1; i < 5; i++) {//遍历四个选项
		if (i == s->correctOption) continue;
		switch (i) {
		case 1:drawtext(s->chineses[s->errorAnswerIndex[j]], &s->rectOptionA, DT_WORDBREAK); break;
		case 2:drawtext(s->chineses[s->errorAnswerIndex[j]], &s->rectOptionB, DT_WORDBREAK); break;
		case 3:drawtext(s->chineses[s->errorAnswerIndex[j]], &s->rectOptionC, DT_WORDBREAK); break;
		case 4:drawtext(s->chineses[s->errorAnswerIndex[j]], &s->rectOptionD, DT_WORDBREAK); break;
		}
		j++;
	}

	//绘制四个选项的imgBingo或imgError
	for (int i = 0; i < 4; i++) {
		struct btn* btnTemp = NULL;
		switch (i) {
		case 0:btnTemp = s->optionABtn; break;
		case 1:btnTemp = s->optionBBtn; break;
		case 2:btnTemp = s->optionCBtn; break;
		case 3:btnTemp = s->optionDBtn; break;
		}
		if (s->selectedOption[i] == true) {
			if (s->correctOption == i + 1) {
				putTransparentImage(NULL, btnTemp->super.x + 500, btnTemp->super.y + 15, s->imgBingo);
				if (s->soundFlag[i]==true) {
					s->soundFlag[i] = false;
					s->isPlayBingoSound = true;
				}
			}
			else {
				putTransparentImage(NULL, btnTemp->super.x + 500, btnTemp->super.y + 15, s->imgError);
				if (s->soundFlag[i] == true) {
					s->soundFlag[i] = false;
					s->isPlayErrorSound = true;
				}
			}
		}
	}
	//打印题号
	settextcolor(BLACK);
	settextstyle(100, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	char str[10];
	sprintf(str, "%d/%d", s->questionIndex + 1, QUESTIONNUMEVERYLEVEL);
	outtextxy(150, 15, str);
	//绘制"下一关"按钮
	if (s->isSuccess == true) {
		s->nextBtn->super.draw((sprite*)s->nextBtn);
	}
}

void levelSceneUpdate(struct levelScene* s, struct gameData* gd)
{
	//生成第一个问题
	if (s->correctOption == -1) {
		s->correctAnswerIndex = s->questionIndex;
		//随机生成正确选项的位置
		int m = 1;
		int n = 4;
		int r = rand() % (n - m + 1) + m;
		s->correctOption = r;
		//随机生成错误的答案
		int* record = (int*)malloc(sizeof(int*) * QUESTIONNUMEVERYLEVEL);
		if (record == NULL) return;
		for (int i = 0; i < QUESTIONNUMEVERYLEVEL; i++) {
			record[i] = 0;
		}
		m = 0;
		n = QUESTIONNUMEVERYLEVEL - 1;
		for (int i = 0; i < 3; i++) {
			int num;
			do {
				num = rand() % (n - m + 1) + m;
			} while (num == s->questionIndex || record[num]);
			s->errorAnswerIndex[i] = num;
			record[num] = 1;
		}
	}
	//生成下一个问题
	if (s->isNext == true) {
		s->isNext = false;
		s->isSuccess = false;
		s->questionIndex++;
		s->correctAnswerIndex = s->questionIndex;
		//随机生成正确选项的位置
		int m = 1;
		int n = 4;
		int r = rand() % (n - m + 1) + m;
		s->correctOption = r;
		//随机生成错误的答案
		int* record = (int*)malloc(sizeof(int*) * QUESTIONNUMEVERYLEVEL);
		if (record == NULL) return;
		for (int i = 0; i < QUESTIONNUMEVERYLEVEL; i++) {
			record[i] = 0;
		}
		m = 0;
		n = QUESTIONNUMEVERYLEVEL - 1;
		for (int i = 0; i < 3; i++) {
			int num;
			do {
				num = rand() % (n - m + 1) + m;
			} while (num == s->questionIndex || record[num]);
			s->errorAnswerIndex[i] = num;
			record[num] = 1;
		}
		//还原selectedOption
		for (int i = 0; i < 4; i++) {
			s->selectedOption[i] = false;
		}
	}
	//判断是否成功
	if (s->selectedOption[s->correctOption - 1] == true) {
		s->isSuccess = true;
		//通关
		if (s->questionIndex == QUESTIONNUMEVERYLEVEL - 1) {
			s->isQuit = true;
			gd->isLevelFinishScene = true;

			if (gd->level == gd->levelSchedule + 1) {
				gd->levelSchedule++;
				gd->pinkballNum += FIRSTPASSREWARDS;
			}
			else {
				gd->pinkballNum += REPEATPASSREWARDS;
			}
		}
	}
	//播放音效
	if(s->isPlayBingoSound == true) {
		s->isPlayBingoSound = false;
		mciSendString("close asset/sounds/bingoSound.wma", NULL, 0, NULL);
		mciSendString("open asset/sounds/bingoSound.wma", NULL, 0, NULL);
		mciSendString("play asset/sounds/bingoSound.wma", NULL, 0, NULL);
	}
	if (s->isPlayErrorSound == true) {
		s->isPlayErrorSound = false;
		mciSendString("close asset/sounds/errorSound.wma", NULL, 0, NULL);
		mciSendString("open asset/sounds/errorSound.wma", NULL, 0, NULL);
		mciSendString("play asset/sounds/errorSound.wma", NULL, 0, NULL);
	}
	//播放读音
	if (s->isPronounce == true) {
		s->isPronounce = false;
		int wordNum = (gd->level - 1) * QUESTIONNUMEVERYLEVEL + s->questionIndex + 1;
		char pronunciationPath[100];
		sprintf(pronunciationPath, "asset/sounds/words_en/%d.mp3", wordNum);
		char command[100];
		sprintf(command, "close %s", pronunciationPath);
		mciSendString(command, NULL, 0, NULL);
		sprintf(command, "open %s", pronunciationPath);
		mciSendString(command, NULL, 0, NULL);
		sprintf(command, "play %s", pronunciationPath);
		mciSendString(command, NULL, 0, NULL);
	}
}

void levelSceneControl(struct levelScene* s,ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (s->isSuccess == false) {
			//这里的代码稍显重复,常规方法无法合并简化,可以用宏定义##
			if (s->rectOptionA.left < msg->x && msg->x < s->rectOptionA.right && s->rectOptionA.bottom > msg->y && msg->y > s->rectOptionA.top)
			{
				if (s->selectedOption[0] == false) {
					s->selectedOption[0] = true;
					s->soundFlag[0] = true;
				}
			}
			if (s->rectOptionB.left < msg->x && msg->x < s->rectOptionB.right && s->rectOptionB.bottom > msg->y && msg->y > s->rectOptionB.top)
			{
				if (s->selectedOption[1] == false) {
					s->selectedOption[1] = true;
					s->soundFlag[1] = true;
				}
			}
			if (s->rectOptionC.left < msg->x && msg->x < s->rectOptionC.right && s->rectOptionC.bottom > msg->y && msg->y > s->rectOptionC.top)
			{
				if (s->selectedOption[2] == false) {
					s->selectedOption[2] = true;
					s->soundFlag[2] = true;
				}
			}
			if (s->rectOptionD.left < msg->x && msg->x < s->rectOptionD.right && s->rectOptionD.bottom > msg->y && msg->y > s->rectOptionD.top)
			{
				if (s->selectedOption[3] == false) {
					s->selectedOption[3] = true;
					s->soundFlag[3] = true;
				}
			}
		}
		if (s->backBtn->super.x < msg->x && msg->x < s->backBtn->super.x + s->backBtn->super.width && s->backBtn->super.y < msg->y && msg->y < s->backBtn->super.y + s->backBtn->super.height)
		{
			s->isQuit = true;
			gd->isSelectLevelScene = true;
		}
		if (s->nextBtn->super.x < msg->x && msg->x < s->nextBtn->super.x + s->nextBtn->super.width && s->nextBtn->super.y < msg->y && msg->y < s->nextBtn->super.y + s->nextBtn->super.height)
		{
			if (s->isSuccess == true) {
				s->isNext = true;
			}
		}

		if (s->pronunciationBtn->super.x < msg->x && msg->x < s->pronunciationBtn->super.x + s->pronunciationBtn->super.width && s->pronunciationBtn->super.y < msg->y && msg->y < s->pronunciationBtn->super.y + s->pronunciationBtn->super.height)
		{
			s->isPronounce = true;
		}
	}
}

bool levelSceneIsQuit(struct levelScene* s, struct gameData* gd)
{
	return s->isQuit;
}

void levelSceneInit(struct levelScene* s,struct gameData* gd)
{
	s->super.draw = (void(*)(struct scene*, struct gameData* gd))levelSceneDraw;
	s->super.update = (void(*)(struct scene*, struct gameData* gd))levelSceneUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))levelSceneControl;
	s->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))levelSceneIsQuit;

	s->bkLevel = new IMAGE;
	loadimage(s->bkLevel, "asset/image/levelScene/bkLevel.jpg");
	s->imgBingo = new IMAGE;
	loadimage(s->imgBingo, "asset/image/levelScene/bingo.png");
	s->imgError = new IMAGE;
	loadimage(s->imgError, "asset/image/levelScene/error.png");

	s->backBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->backBtn, 0, 0, 128, 129, "asset/image/levelScene/backBtn.png");
	s->optionABtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionABtn, 250, 300, 600, 200, "asset/image/levelScene/optionBtn.png");
	s->optionBBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionBBtn, 1050, 300, 600, 200, "asset/image/levelScene/optionBtn.png");
	s->optionCBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionCBtn, 250, 500, 600, 200, "asset/image/levelScene/optionBtn.png");
	s->optionDBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionDBtn, 1050, 500, 600, 200, "asset/image/levelScene/optionBtn.png");
	s->nextBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->nextBtn, 600, 750, 750, 288, "asset/image/levelScene/nextBtn.png");
	s->pronunciationBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->pronunciationBtn, 908, 253, 78, 78, "asset/image/levelScene/pronunciation.png");

	s->rectOptionA = { 250,330,850,530 };
	s->rectOptionB = { 1050,330,1650,530 };
	s->rectOptionC = { 250,530,850,730 };
	s->rectOptionD = { 1050,530,1650,730 };
	s->rectQuestion = { 250,100,1650,250 };

	for (int i = 0; i < 4; i++) {
		s->selectedOption[i] = false;
	}

	s->isQuit = false;
	s->isNext = false;
	s->isSuccess = false;

	s->correctOption = -1;
	
	s->questionIndex = 0;

	char wordsTxtPath[50];
	char chinesesTxtPath[50];
	sprintf(wordsTxtPath, "asset/wordList/%d_words.txt", gd->level);
	sprintf(chinesesTxtPath, "asset/wordList/%d_chineses.txt", gd->level);
	FILE* file1, * file2;
	file1 = fopen(wordsTxtPath, "r");
	file2 = fopen(chinesesTxtPath, "r");
	if (file1 == NULL) return;
	if (file2 == NULL) return;
	for (int i = 0; i < QUESTIONNUMEVERYLEVEL; i++) {
		fgets(s->words[i], sizeof(s->words[i]), file1);
		fgets(s->chineses[i], sizeof(s->chineses[i]), file2);
	}
	fclose(file1);
	fclose(file2);

	s->isPlayBingoSound = false;
	s->isPlayErrorSound = false;
	s->isPronounce = false;

	for (int i = 0; i < 4; i++) {
		s->soundFlag[i] = false;
	}
}

void levelSceneDestroy(struct levelScene* s)
{
	delete s->bkLevel;
	delete s->imgBingo;
	delete s->imgError;

	btnDestroy(s->backBtn);
	free(s->backBtn);
	btnDestroy(s->optionABtn);
	free(s->optionABtn);
	btnDestroy(s->optionBBtn);
	free(s->optionBBtn);
	btnDestroy(s->optionCBtn);
	free(s->optionCBtn);
	btnDestroy(s->optionDBtn);
	free(s->optionDBtn);
	btnDestroy(s->nextBtn);
	free(s->nextBtn);
	btnDestroy(s->pronunciationBtn);
	free(s->pronunciationBtn);
}