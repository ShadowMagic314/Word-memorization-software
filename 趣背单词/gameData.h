#pragma once
#include"vector.h"

//包含的存储库
#include"characterDatabase.h"

struct countdown {
	int hh;
	int mm;
	int ss;
};

struct gameData {
	void (*load)(struct gameData*);
	void (*save)(struct gameData*);

	//数据库
	struct characterDatabase characterDB;

	//需要存取的数据
	int gachaTimes;
	int exp;
	int pinkballNum;
	int levelSchedule;//1~120//1完成后是1
	int purpleMinimumGuaranteeCnt;
	int goldMinimumGuaranteeCnt;
	int bigMinimumGuaranteeCnt;
	bool* ownFiveStarCharacters;
	bool* ownFourStarCharacters;

	//通用数据
	int level;//1~10

	bool isExit;

	bool isGachaScene;
	bool isLevelScane;
	bool isLevelFinishScene;
	bool isSelectLevelScene;
	bool isMenuScene;

	bool isDeveloperMode;

	bool isbkMusic;

	int mode;
	/* 1-经典模式
	   2-限时模式
	   3-无尽模式
	*/
	int lastMode;
	bool isSwitchMode;

	struct countdown* countdown;//限时模式的倒计时时间

	int difficultyGrade;//无尽模式的难度等级//1-简单 2-困难 3-噩梦
};

void gameDataInit(struct gameData*gd);
void gameDataDestroy(struct gameData* gd);