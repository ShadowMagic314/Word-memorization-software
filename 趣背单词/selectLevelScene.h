#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "scene.h"
#include "gameData.h"
#include "image.h"
#include "btn.h"
#include <stdio.h>

#define LEVEL_NUM 120//���йؿ�����
#define LEVEL_NUM_EVERY_PAGE 20//ÿһҳ�ؿ���

struct selectLevelScene {
	struct scene super;

	IMAGE* bkSelectLevel;
	IMAGE* levelBlock;
	IMAGE* titleImg;
	IMAGE* voidstar;
	IMAGE* fullstar;

	RECT* rectLevels;//ÿһ���ؿ���

	int selectedLevel;//��ʵ������1��ʼ
	int pageNum;//�����ǵڼ�ҳ��1��ʼ
	int selectErrorCnt;

	bool isQuit;

	btn* homeBtn;
	btn* pgupBtn;
	btn* pgdnBtn;

	bool isSelectError;//Խ��ѡ��
};

void selectLevelSceneInit(struct selectLevelScene* s);
void selectLevelSceneDestroy(struct selectLevelScene* s);