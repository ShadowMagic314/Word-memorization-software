#pragma once
#include"vector.h"

//包含的存储库
#include"characterDatabase.h"

struct gameData {
	void (*load)(struct gameData*);
	void (*save)(struct gameData*);

	//数据库
	struct characterDatabase characterDB;

	//需要存取的数据
	int gachaTimes;
	int exp;
	int pinkballNum;
	int levelSchedule;//1~20//1完成后是1
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
};

void gameDataInit(struct gameData*gd);
void gameDataDestroy(struct gameData* gd);