#pragma once
#include"vector.h"

//�����Ĵ洢��
#include"characterDatabase.h"

struct countdown {
	int hh;
	int mm;
	int ss;
};

struct gameData {
	void (*load)(struct gameData*);
	void (*save)(struct gameData*);

	//���ݿ�
	struct characterDatabase characterDB;

	//��Ҫ��ȡ������
	int gachaTimes;
	int exp;
	int pinkballNum;
	int levelSchedule;//1~120//1��ɺ���1
	int purpleMinimumGuaranteeCnt;
	int goldMinimumGuaranteeCnt;
	int bigMinimumGuaranteeCnt;
	bool* ownFiveStarCharacters;
	bool* ownFourStarCharacters;

	//ͨ������
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
	/* 1-����ģʽ
	   2-��ʱģʽ
	   3-�޾�ģʽ
	*/
	int lastMode;
	bool isSwitchMode;

	struct countdown* countdown;//��ʱģʽ�ĵ���ʱʱ��

	int difficultyGrade;//�޾�ģʽ���Ѷȵȼ�//1-�� 2-���� 3-ج��
};

void gameDataInit(struct gameData*gd);
void gameDataDestroy(struct gameData* gd);