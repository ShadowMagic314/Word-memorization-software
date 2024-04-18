#include "levelClassics.h"

void levelClassicsDraw(struct levelClassics* s, struct gameData* gd)
{
	putimage(0, 0, s->bk);

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
				putTransparentImage(NULL, btnTemp->super.x + 550, btnTemp->super.y + 30, s->imgBingo);
				if (s->soundFlag[i]==true) {
					s->soundFlag[i] = false;
					s->isPlayBingoSound = true;
				}
			}
			else {
				putTransparentImage(NULL, btnTemp->super.x + 550, btnTemp->super.y + 30, s->imgError);
				if (s->soundFlag[i] == true) {
					s->soundFlag[i] = false;
					s->isPlayErrorSound = true;

					if (gd->isDeveloperMode == false) {
						s->errorCnt++;
					}
				}
			}
		}
	}

	//播放音效
	if (s->isPlayBingoSound == true) {
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

	//打印命数
	switch (s->errorCnt)
	{
	case 0:putTransparentImage(NULL, 1492, 30, s->threeHearts); break;
	case 1:putTransparentImage(NULL, 1492, 30, s->twoHearts); break;
	case 2:putTransparentImage(NULL, 1492, 30, s->oneHearts); break;
	case 3:putTransparentImage(NULL, 1492, 30, s->zeroHearts);  break;
	}

	//打印题号
	settextcolor(BLACK);
	settextstyle(100, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	char str[10];
	sprintf(str, "%d/%d", s->questionIndex + 1, QUESTION_NUM_EVERY_LEVEL);
	outtextxy(150, 15, str);
	//绘制"下一关"按钮
	if (s->isSuccess == true) {
		s->nextBtn->super.draw((sprite*)s->nextBtn);
	}
}

void levelClassicsUpdate(struct levelClassics* s, struct gameData* gd)
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
		int* record = (int*)malloc(sizeof(int*) * QUESTION_NUM_EVERY_LEVEL);
		if (record == NULL) return;
		for (int i = 0; i < QUESTION_NUM_EVERY_LEVEL; i++) {
			record[i] = 0;
		}
		m = 0;
		n = QUESTION_NUM_EVERY_LEVEL - 1;
		for (int i = 0; i < 3; i++) {
			int num;
			do {
				num = rand() % (n - m + 1) + m;
			} while (num == s->questionIndex || record[num]);
			s->errorAnswerIndex[i] = num;
			record[num] = 1;
		}
		free(record);
	}
	//生成下一个问题
	if (s->isNext == true) {
		s->isNext = false;
		s->isSuccess = false;
		s->isPronounce = true;
		s->questionIndex++;
		s->correctAnswerIndex = s->questionIndex;
		//随机生成正确选项的位置
		int m = 1;
		int n = 4;
		int r = rand() % (n - m + 1) + m;
		s->correctOption = r;
		//随机生成错误的答案
		int* record = (int*)malloc(sizeof(int*) * QUESTION_NUM_EVERY_LEVEL);
		if (record == NULL) return;
		for (int i = 0; i < QUESTION_NUM_EVERY_LEVEL; i++) {
			record[i] = 0;
		}
		m = 0;
		n = QUESTION_NUM_EVERY_LEVEL - 1;
		for (int i = 0; i < 3; i++) {
			int num;
			do {
				num = rand() % (n - m + 1) + m;
			} while (num == s->questionIndex || record[num]);
			s->errorAnswerIndex[i] = num;
			record[num] = 1;
		}
		free(record);
		//还原selectedOption
		for (int i = 0; i < 4; i++) {
			s->selectedOption[i] = false;
		}
	}

	//判断错误次数是否达到三个
	if (s->errorCnt == 3) {
		s->isQuit = true;
		putTransparentImage(NULL, 0, 0, s->badend);//以后需要改成bool
		FlushBatchDraw();
		Sleep(2000);
		gd->isSelectLevelScene = true;
	}

	//判断是否成功
	if (s->selectedOption[s->correctOption - 1] == true) {
		s->isSuccess = true;
		//通关
		if (s->questionIndex == QUESTION_NUM_EVERY_LEVEL - 1) {
			s->isQuit = true;
			gd->isLevelFinishScene = true;

			if (gd->level == gd->levelSchedule + 1) {
				gd->levelSchedule++;
				gd->pinkballNum += FIRST_PASS_REWARDS;
			}
			else {
				gd->pinkballNum += REPEAT_PASS_REWARDS;
			}
			gd->save(gd);//在这里存一次档
		}
	}
	
	//播放读音
	if (s->isPronounce == true) {
		s->isPronounce = false;
		char pronunciationPath[100];
		char* temp;
		temp = strchr(s->words[s->questionIndex], '\n');
		if (temp != NULL) {
			*temp = '\0';
		}
		sprintf(pronunciationPath, "asset/sounds/words_en/%s.wma", s->words[s->questionIndex]);
		char command[100];
		sprintf(command, "close %s", pronunciationPath);
		mciSendString(command, NULL, 0, NULL);
		sprintf(command, "open %s", pronunciationPath);
		mciSendString(command, NULL, 0, NULL);
		sprintf(command, "play %s", pronunciationPath);
		mciSendString(command, NULL, 0, NULL);
	}
}

void levelClassicsControl(struct levelClassics* s,ExMessage* msg, struct gameData* gd)
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
		if (BTN_RANGE(s->backBtn))
		{
			s->isQuit = true;
			gd->isSelectLevelScene = true;
		}
		if (BTN_RANGE(s->nextBtn))
		{
			if (s->isSuccess == true) {
				s->isNext = true;
			}
		}

		if (BTN_RANGE(s->pronunciationBtn))
		{
			s->isPronounce = true;
		}
	}
}

bool levelClassicsIsQuit(struct levelClassics* s, struct gameData* gd)
{
	return s->isQuit;
}

void levelClassicsInit(struct levelClassics* s,struct gameData* gd)
{
	s->super.draw = (void(*)(struct scene*, struct gameData* gd))levelClassicsDraw;
	s->super.update = (void(*)(struct scene*, struct gameData* gd))levelClassicsUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))levelClassicsControl;
	s->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))levelClassicsIsQuit;

	s->bk = new IMAGE;
	loadimage(s->bk, "asset/levelScene/classics/bk.jpg");
	s->imgBingo = new IMAGE;
	loadimage(s->imgBingo, "asset/levelScene/classics/bingo.png");
	s->imgError = new IMAGE;
	loadimage(s->imgError, "asset/levelScene/classics/error.png");
	s->threeHearts = new IMAGE;
	loadimage(s->threeHearts, "asset/levelScene/classics/threeHearts.png");
	s->twoHearts = new IMAGE;
	loadimage(s->twoHearts, "asset/levelScene/classics/twoHearts.png");
	s->oneHearts = new IMAGE;
	loadimage(s->oneHearts, "asset/levelScene/classics/oneHearts.png");
	s->zeroHearts = new IMAGE;
	loadimage(s->zeroHearts, "asset/levelScene/classics/zeroHearts.png");
	s->badend = new IMAGE;
	loadimage(s->badend, "asset/levelScene/classics/badend.png");

	s->backBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->backBtn, 0, 0, 128, 129, "asset/levelScene/classics/backBtn.png");
	s->optionABtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionABtn, 253, 351, 655, 233, "asset/levelScene/classics/optionBtn.png");
	s->optionBBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionBBtn, 1003, 351, 655, 233, "asset/levelScene/classics/optionBtn.png");
	s->optionCBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionCBtn, 253, 625, 655, 233, "asset/levelScene/classics/optionBtn.png");
	s->optionDBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionDBtn, 1003, 625, 655, 233, "asset/levelScene/classics/optionBtn.png");
	s->nextBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->nextBtn, 707,878,507,151, "asset/levelScene/classics/nextBtn.png"); 
	s->pronunciationBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->pronunciationBtn, 908, 253, 78, 78, "asset/levelScene/classics/pronunciation.png");

	s->rectOptionA = { 280,361,881,574 };//+27,+10,+601,+213
	s->rectOptionB = { 1030,361,1631,574 };
	s->rectOptionC = { 280,635,881,848 };
	s->rectOptionD = { 1030,635,1631,848 };
	s->rectQuestion = { 250,100,1650,250 };

	for (int i = 0; i < 4; i++) {
		s->selectedOption[i] = false;
	}

	s->isQuit = false;
	s->isNext = true;
	s->isSuccess = false;

	s->correctOption = -1;
	
	s->questionIndex = -1;//开始就+1

	char wordsTxtPath[50];
	char chinesesTxtPath[50];
	sprintf(wordsTxtPath, "asset/wordList/%d_words.txt", gd->level);
	sprintf(chinesesTxtPath, "asset/wordList/%d_chineses.txt", gd->level);
	FILE* file1, * file2;
	file1 = fopen(wordsTxtPath, "r");
	file2 = fopen(chinesesTxtPath, "r");
	if (file1 == NULL) return;
	if (file2 == NULL) return;
	for (int i = 0; i < QUESTION_NUM_EVERY_LEVEL; i++) {
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

	s->errorCnt = 0;
}

void levelClassicsDestroy(struct levelClassics* s)
{
	delete s->bk;
	delete s->imgBingo;
	delete s->imgError;
	delete s->threeHearts;
	delete s->twoHearts;
	delete s->oneHearts;
	delete s->zeroHearts;
	delete s->badend;

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