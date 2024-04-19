#include "levelEndless.h"

void countdownChange(struct countdown* cd, int ds) {
	// 将秒数转换为时、分、秒
	int seconds = cd->ss + ds;
	int minutes = cd->mm;
	int hours = cd->hh;

	// 处理秒数
	while (seconds >= 60) {
		seconds -= 60;
		minutes++;
	}
	while (seconds < 0) {
		seconds += 60;
		minutes--;
	}

	// 处理分钟
	while (minutes >= 60) {
		minutes -= 60;
		hours++;
	}
	while (minutes < 0) {
		minutes += 60;
		hours--;
	}

	// 处理小时
	if (hours < 0) {
		hours = 0;
		minutes = 0;
		seconds = 0;
	}

	// 更新结构体中的值
	cd->hh = hours;
	cd->mm = minutes;
	cd->ss = seconds;
}

void levelEndlessDraw(struct levelEndless* s, struct gameData* gd)
{
	putimage(0, 0, s->bk);

	if (s->isBackBtnHover == false) {
		s->backBtn->super.draw((sprite*)s->backBtn);
	}
	else
	{
		s->bigBackBtn->super.draw((sprite*)s->bigBackBtn);
	}

	if (s->isBigOptionABtnHover == false) {
		s->optionABtn->super.draw((sprite*)s->optionABtn);
	}
	else
	{
		s->bigOptionABtn->super.draw((sprite*)s->bigOptionABtn);
	}

	if (s->isBigOptionBBtnHover == false) {
		s->optionBBtn->super.draw((sprite*)s->optionBBtn);
	}
	else
	{
		s->bigOptionBBtn->super.draw((sprite*)s->bigOptionBBtn);
	}

	if (s->isBigOptionCBtnHover == false) {
		s->optionCBtn->super.draw((sprite*)s->optionCBtn);
	}
	else
	{
		s->bigOptionCBtn->super.draw((sprite*)s->bigOptionCBtn);
	}

	if (s->isBigOptionDBtnHover == false) {
		s->optionDBtn->super.draw((sprite*)s->optionDBtn);
	}
	else
	{
		s->bigOptionDBtn->super.draw((sprite*)s->bigOptionDBtn);
	}

	if (s->isBigPronunciationBtnHover == false) {
		s->pronunciationBtn->super.draw((sprite*)s->pronunciationBtn);
	}
	else
	{
		s->bigPronunciationBtn->super.draw((sprite*)s->bigPronunciationBtn);
	}

	putTransparentImage(NULL, 1220, 12, s->bkCountdown);

	settextcolor(BLACK);
	settextstyle(140, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	drawtext(s->word, &s->rectQuestion, DT_CENTER);

	settextcolor(BLACK);
	settextstyle(50, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	//打印正确选项
	switch (s->correctOption) {
	case 1:drawtext(s->chinese, &s->rectOptionA, DT_WORDBREAK); break;
	case 2:drawtext(s->chinese, &s->rectOptionB, DT_WORDBREAK); break;
	case 3:drawtext(s->chinese, &s->rectOptionC, DT_WORDBREAK); break;
	case 4:drawtext(s->chinese, &s->rectOptionD, DT_WORDBREAK); break;
	}

	//打印错误选项
	int j = 0;//遍历三个错误答案
	for (int i = 1; i < 5; i++) {//遍历四个选项
		if (i == s->correctOption) continue;
		switch (i) {
		case 1:drawtext(s->wrongChinese[j], &s->rectOptionA, DT_WORDBREAK); break;
		case 2:drawtext(s->wrongChinese[j], &s->rectOptionB, DT_WORDBREAK); break;
		case 3:drawtext(s->wrongChinese[j], &s->rectOptionC, DT_WORDBREAK); break;
		case 4:drawtext(s->wrongChinese[j], &s->rectOptionD, DT_WORDBREAK); break;
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
				if (s->soundFlag[i] == true) {
					s->soundFlag[i] = false;
					s->isPlayBingoSound = true;
					s->mark += 2;
					switch (gd->difficultyGrade) {
					case 1:countdownChange(s->countdown, 30); break;
					case 2:countdownChange(s->countdown, 20); break;
					case 3:countdownChange(s->countdown, 10); break;
					}
				}
			}
			else {
				putTransparentImage(NULL, btnTemp->super.x + 550, btnTemp->super.y + 30, s->imgError);
				if (s->soundFlag[i] == true) {
					s->soundFlag[i] = false;
					s->isPlayErrorSound = true;
					if (gd->isDeveloperMode == false) {
						switch (gd->difficultyGrade) {
						case 1:countdownChange(s->countdown, -10); break;
						case 2:countdownChange(s->countdown, -20); break;
						case 3:countdownChange(s->countdown, -30); break;
						}
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

	//绘制"下一关"按钮
	if (s->isSelectFinish == true) {
		if (s->isNextBtnHover == false) {
			s->nextBtn->super.draw((sprite*)s->nextBtn);
		}
		else
		{
			s->bigNextBtn->super.draw((sprite*)s->bigNextBtn);
		}
	}

	settextcolor(BLUE);
	settextstyle(150, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	char strCountdown[30];
	sprintf(strCountdown, "%02d:%02d:%02d", s->countdown->hh, s->countdown->mm, s->countdown->ss);
	outtextxy(1400, 20, strCountdown);

	settextcolor(WHITE);
	settextstyle(130, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	char strMark[30];
	sprintf(strMark, "得分:%d", s->mark);
	outtextxy(180, 20, strMark);

	if (s->isFinish) {
		cleardevice();
		settextcolor(BLACK);
		settextstyle(250, 0, "微软雅黑");
		setbkmode(TRANSPARENT);
		char strMark[30];
		sprintf(strMark, "最终得分:%d", s->mark);
		outtextxy(500, 300, strMark);
		int reward = 0;
		if (s->mark > 0) {
			reward = s->mark / 10;
		}
		char strReward[30];
		sprintf(strReward, "奖励%d个粉球", reward);
		gd->pinkballNum += reward;
		gd->save(gd);
		outtextxy(500, 500, strReward);
		FlushBatchDraw();
		Sleep(3000);
		s->isQuit = true;
		gd->isSelectLevelScene = true;
	}
}

void levelEndlessUpdate(struct levelEndless* s, struct gameData* gd)
{
	//生成下一个问题
	if (s->isNext == true) {
		s->isNext = false;
		s->isPronounce = true;
		//随机生成正确选项的位置
		int m = 1;
		int n = 4;
		int r = rand() % (n - m + 1) + m;
		s->correctOption = r;
		char wordsTxtPath[50];
		char chinesesTxtPath[50];
		do {
			m = 1; n = LEVEL_NUM;
			s->randLevel = rand() % (n - m + 1) + m;
			m = 1; n = QUESTION_NUM_EVERY_LEVEL;
			s->randIndex = rand() % (n - m + 1) + m;
		} while (s->wordListsFlag[s->randLevel][s->randIndex] == true);
		s->wordListsFlag[s->randLevel][s->randIndex] = true;
		sprintf(wordsTxtPath, "asset/wordList/%d_words.txt", s->randLevel);
		sprintf(chinesesTxtPath, "asset/wordList/%d_chineses.txt", s->randLevel);
		FILE* file1, * file2;
		file1 = fopen(wordsTxtPath, "r");
		file2 = fopen(chinesesTxtPath, "r");
		if (file1 == NULL) return;
		if (file2 == NULL) return;
		int currentLine = 0;
		while (fgets(s->word, sizeof(s->word), file1) != NULL) {
			currentLine++;
			if (currentLine == s->randIndex) {
				// 找到目标行
				currentLine = 0;
				fclose(file1);
			}
		}
		while (fgets(s->chinese, sizeof(s->chinese), file2) != NULL) {
			currentLine++;
			if (currentLine == s->randIndex) {
				// 找到目标行
				currentLine = 0;
				fclose(file2);
			}
		}
		//在本关的汉语里随机生成错误的答案
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
			} while (num == s->randIndex - 1 || record[num]);
			s->errorAnswerIndex[i] = num;
			record[num] = 1;
		}
		free(record);
		for (int i = 0; i < 3; i++) {
			file2 = fopen(chinesesTxtPath, "r");
			while (fgets(s->wrongChinese[i], sizeof(s->wrongChinese[i]), file2) != NULL) {
				currentLine++;
				if (currentLine == s->errorAnswerIndex[i] + 1) {
					// 找到目标行
					currentLine = 0;
					fclose(file2);
					break;
				}
			}
		}
		//还原selectedOption
		for (int i = 0; i < 4; i++) {
			s->selectedOption[i] = false;
		}
	}

	//检测是否已经选择
	for (int i = 0; i < 4; i++) {
		if (s->selectedOption[i] == true) {
			s->isSelectFinish = true;
			break;
		}
	}

	if (s->isPronounce == true) {
		s->isPronounce = false;
		char pronunciationPath[100];
		char* temp;
		temp = strchr(s->word, '\n');
		if (temp != NULL) {
			*temp = '\0';
		}
		sprintf(pronunciationPath, "asset/sounds/words_en/%s.wma", s->word);
		char command[100];
		sprintf(command, "close %s", pronunciationPath);
		mciSendString(command, NULL, 0, NULL);
		sprintf(command, "open %s", pronunciationPath);
		mciSendString(command, NULL, 0, NULL);
		sprintf(command, "play %s", pronunciationPath);
		mciSendString(command, NULL, 0, NULL);
	}

	s->timingNow = clock();
	if (((s->timingNow - s->timingStart) / CLOCKS_PER_SEC >= 1.0)) { // 检查是否过去了一秒
		s->timingStart = s->timingNow;
		s->isCountdownUpdate = true;
	}

	if (s->isCountdownUpdate) {
		s->isCountdownUpdate = false;
		if (s->countdown->ss > 0) {
			s->countdown->ss--;
		}
		else if (s->countdown->mm > 0) {
			s->countdown->mm--;
			s->countdown->ss = 59;
		}
		else if (s->countdown->hh > 0) {
			s->countdown->hh--;
			s->countdown->mm = 59;
			s->countdown->ss = 59;
		}
		else {
			s->isFinish = true;
		}
	}
}

void levelEndlessControl(struct levelEndless* s, ExMessage* msg, struct gameData* gd)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (s->isSelectFinish == false) {
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
			s->isFinish = true;
		}
		if (BTN_RANGE(s->nextBtn))
		{
			if (s->isSelectFinish == true) {
				s->isSelectFinish = false;
				s->isNext = true;
			}
		}

		if (BTN_RANGE(s->pronunciationBtn))
		{
			s->isPronounce = true;
		}
	}

	if (msg->message == WM_MOUSEMOVE) {
		s->isBackBtnHover = false;
		s->isBigOptionABtnHover = false;
		s->isBigOptionBBtnHover = false;
		s->isBigOptionCBtnHover = false;
		s->isBigOptionDBtnHover = false;
		s->isBigPronunciationBtnHover = false;
		s->isNextBtnHover = false;

		if (BTN_RANGE(s->nextBtn)) {
			s->isNextBtnHover = true;
		}
		if (BTN_RANGE(s->optionABtn)) {
			s->isBigOptionABtnHover = true;
		}
		if (BTN_RANGE(s->optionBBtn)) {
			s->isBigOptionBBtnHover = true;
		}
		if (BTN_RANGE(s->optionCBtn)) {
			s->isBigOptionCBtnHover = true;
		}
		if (BTN_RANGE(s->optionDBtn)) {
			s->isBigOptionDBtnHover = true;
		}
		if (BTN_RANGE(s->pronunciationBtn)) {
			s->isBigPronunciationBtnHover = true;
		}
		if (BTN_RANGE(s->bigBackBtn)) {
			s->isBackBtnHover = true;
		}
	}
}

bool levelEndlessIsQuit(struct levelEndless* s, struct gameData* gd)
{
	return s->isQuit;
}

void levelEndlessInit(struct levelEndless* s, struct gameData* gd)
{
	s->super.draw = (void(*)(struct scene*, struct gameData* gd))levelEndlessDraw;
	s->super.update = (void(*)(struct scene*, struct gameData* gd))levelEndlessUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*, struct gameData* gd))levelEndlessControl;
	s->super.isQuit = (bool(*)(struct scene*, struct gameData* gd))levelEndlessIsQuit;

	s->bk = new IMAGE;
	loadimage(s->bk, "asset/levelScene/endless/bk.jpg");
	s->imgBingo = new IMAGE;
	loadimage(s->imgBingo, "asset/levelScene/endless/bingo.png");
	s->imgError = new IMAGE;
	loadimage(s->imgError, "asset/levelScene/endless/error.png");
	s->bkCountdown = new IMAGE;
	loadimage(s->bkCountdown, "asset/levelScene/endless/bkCountdown.png");

	s->backBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->backBtn, 28, 23, 128, 129, "asset/levelScene/endless/backBtn.png");
	s->bigBackBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigBackBtn, 23, 17, 139, 141, "asset/levelScene/endless/bigBackBtn.png");
	s->optionABtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionABtn, 253, 351, 655, 233, "asset/levelScene/endless/optionBtn.png");
	s->bigOptionABtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigOptionABtn, 242, 343, 677, 249, "asset/levelScene/endless/bigOptionBtn.png");
	s->optionBBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionBBtn, 1003, 351, 655, 233, "asset/levelScene/endless/optionBtn.png");
	s->bigOptionBBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigOptionBBtn, 991, 343, 678, 249, "asset/levelScene/endless/bigOptionBtn.png");
	s->optionCBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionCBtn, 253, 625, 655, 233, "asset/levelScene/endless/optionBtn.png");
	s->bigOptionCBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigOptionCBtn, 245, 616, 673, 251, "asset/levelScene/endless/bigOptionBtn.png");
	s->optionDBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->optionDBtn, 1003, 625, 655, 233, "asset/levelScene/endless/optionBtn.png");
	s->bigOptionDBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigOptionDBtn, 992, 616, 677, 251, "asset/levelScene/endless/bigOptionBtn.png");
	s->nextBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->nextBtn, 707, 878, 507, 151, "asset/levelScene/endless/nextBtn.png");
	s->bigNextBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigNextBtn, 701, 873, 519, 162, "asset/levelScene/endless/bigNextBtn.png");
	s->pronunciationBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->pronunciationBtn, 908, 253, 78, 78, "asset/levelScene/endless/pronunciation.png");
	s->bigPronunciationBtn = (struct btn*)malloc(sizeof(struct btn));
	btnInit(s->bigPronunciationBtn, 903, 248, 87, 87, "asset/levelScene/endless/bigPronunciation.png");

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
	s->wordListsFlag = (bool**)malloc((LEVEL_NUM + 1) * sizeof(bool*));
	if (s->wordListsFlag == NULL) return;
	for (int i = 0; i < LEVEL_NUM + 1; i++) {
		s->wordListsFlag[i] = (bool*)malloc((QUESTION_NUM_EVERY_LEVEL + 1) * sizeof(bool));
		if (s->wordListsFlag[i] == NULL) return;
	}
	for (int i = 0; i < LEVEL_NUM + 1; i++) {
		for (int j = 0; j < QUESTION_NUM_EVERY_LEVEL + 1; j++) {
			s->wordListsFlag[i][j] = false;
		}
	}

	s->correctOption = -1;

	s->randIndex = -1;//开始就+1

	s->mark = 0;

	s->isPlayBingoSound = false;
	s->isPlayErrorSound = false;
	s->isPronounce = false;
	s->isSelectFinish = false;
	s->isFinish = false;

	s->isNextBtnHover = false;
	s->isBigOptionABtnHover = false;
	s->isBigOptionBBtnHover = false;
	s->isBigOptionCBtnHover = false;
	s->isBigOptionDBtnHover = false;
	s->isBigPronunciationBtnHover = false;
	s->isBackBtnHover = false;

	for (int i = 0; i < 4; i++) {
		s->soundFlag[i] = false;
	}

	s->countdown = (struct countdown*)malloc(sizeof(struct countdown));
	if (s->countdown == NULL) return;
	s->timingStart = clock();
	switch (gd->difficultyGrade) {
	case 1:s->countdown->hh = 0; s->countdown->mm = 10; s->countdown->ss = 0; s->isCountdownUpdate = true; break;
	case 2:s->countdown->hh = 0; s->countdown->mm = 5; s->countdown->ss = 0; s->isCountdownUpdate = true; break;
	case 3:s->countdown->hh = 0; s->countdown->mm = 1; s->countdown->ss = 0; s->isCountdownUpdate = true; break;
	}
}

void levelEndlessDestroy(struct levelEndless* s)
{
	delete s->bk;
	delete s->imgBingo;
	delete s->imgError;
	delete s->bkCountdown;

	btnDestroy(s->backBtn);
	free(s->backBtn);
	btnDestroy(s->bigBackBtn);
	free(s->bigBackBtn);
	btnDestroy(s->optionABtn);
	free(s->optionABtn);
	btnDestroy(s->bigOptionABtn);
	free(s->bigOptionABtn);
	btnDestroy(s->optionBBtn);
	free(s->optionBBtn);
	btnDestroy(s->bigOptionBBtn);
	free(s->bigOptionBBtn);
	btnDestroy(s->optionCBtn);
	free(s->optionCBtn);
	btnDestroy(s->bigOptionCBtn);
	free(s->bigOptionCBtn);
	btnDestroy(s->optionDBtn);
	free(s->optionDBtn);
	btnDestroy(s->bigOptionDBtn);
	free(s->bigOptionDBtn);
	btnDestroy(s->nextBtn);
	free(s->nextBtn);
	btnDestroy(s->bigNextBtn);
	free(s->bigNextBtn);
	btnDestroy(s->pronunciationBtn);
	free(s->pronunciationBtn);
	btnDestroy(s->bigPronunciationBtn);
	free(s->bigPronunciationBtn);

	for (int i = 0; i < LEVEL_NUM; i++) {
		free(s->wordListsFlag[i]);
	}
	free(s->wordListsFlag);

	free(s->countdown);
}