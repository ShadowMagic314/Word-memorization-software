#include"gameData.h"

void gameDataLoad(struct gameData* gd)//读档函数
{
	FILE* gdFile = fopen("gamedata.dat", "r");
	if (gdFile == NULL) return;

	char str[10];
	fgets(str, sizeof(str), gdFile);
	gd->gachaTimes = atoi(str);
	fgets(str, sizeof(str), gdFile);
	gd->exp = atoi(str);
	fgets(str, sizeof(str), gdFile);
	gd->pinkballNum = atoi(str);
	fgets(str, sizeof(str), gdFile);
	gd->levelSchedule = atoi(str);
	fgets(str, sizeof(str), gdFile);
	gd->purpleMinimumGuaranteeCnt = atoi(str);
	fgets(str, sizeof(str), gdFile);
	gd->goldMinimumGuaranteeCnt = atoi(str);

	for (int i = 0; i < FIVE_STAR_CHARACTERNUM; i++) {
		fgets(str, sizeof(str), gdFile);
		int num = atoi(str);
		if (num == 0) {
			gd->ownFiveStarCharacters[i] = false;
		}
		else {
			gd->ownFiveStarCharacters[i] = true;
		}
	}
	for (int i = 0; i < FOUR_STAR_CHARACTERNUM; i++) {
		fgets(str, sizeof(str), gdFile);
		int num = atoi(str);
		if (num == 0) {
			gd->ownFourStarCharacters[i] = false;
		}
		else {
			gd->ownFourStarCharacters[i] = true;
		}
	}

	fclose(gdFile);
}

void gameDataSave(struct gameData* gd)//存档函数
{
	FILE* gdFile = fopen("gamedata.dat", "w");
	if (gdFile == NULL) return;

	char str[20];
	sprintf(str, "%d\n", gd->gachaTimes);
	fputs(str, gdFile);
	sprintf(str, "%d\n", gd->exp);
	fputs(str, gdFile);
	sprintf(str, "%d\n", gd->pinkballNum);
	fputs(str, gdFile);
	sprintf(str, "%d\n", gd->levelSchedule);
	fputs(str, gdFile);
	sprintf(str, "%d\n", gd->purpleMinimumGuaranteeCnt);
	fputs(str, gdFile);
	sprintf(str, "%d\n", gd->goldMinimumGuaranteeCnt);
	fputs(str, gdFile);

	for (int i = 0; i < FIVE_STAR_CHARACTERNUM; i++) {
		if (gd->ownFiveStarCharacters[i] == true) {
			fputs("1\n", gdFile);
		}
		else {
			fputs("0\n", gdFile);
		}
	}
	for (int i = 0; i < FOUR_STAR_CHARACTERNUM; i++) {
		if (gd->ownFiveStarCharacters[i] == true) {
			fputs("1\n", gdFile);
		}
		else {
			fputs("0\n", gdFile);
		}
	}

	fclose(gdFile);
}

void gameDataInit(struct gameData* gd)
{
	gd->load = (void (*)(struct gameData*))gameDataLoad;
	gd->save = (void (*)(struct gameData*))gameDataSave;

	characterDatabaseInit(&gd->characterDB);

	gd->gachaTimes = 0;
	gd->exp = 0;
	gd->pinkballNum = 0;
	gd->levelSchedule = 0;

	gd->purpleMinimumGuaranteeCnt = 0;
	gd->goldMinimumGuaranteeCnt = 0;
	gd->bigMinimumGuaranteeCnt = 0;

	gd->ownFiveStarCharacters = (bool*)malloc(sizeof(bool) * gd->characterDB.fiveStarCharacterNum);
	if (gd->ownFiveStarCharacters == NULL) return;
	gd->ownFourStarCharacters = (bool*)malloc(sizeof(bool) * gd->characterDB.fourStarCharacterNum);
	if (gd->ownFourStarCharacters == NULL) return;

	gd->level = -1;
	gd->isExit = false;

	gd->isLevelScane = false;
	gd->isGachaScene = false;
	gd->isLevelFinishScene = false;
	gd->isSelectLevelScene = false;
	gd->isMenuScene = true;

	gd->isDeveloperMode = false;

	gd->isbkMusic = false;

	gd->mode = 1;//开始是经典模式
	gd->lastMode = 1;

	gd->lastMode = -1;
	gd->isSwitchMode = false;

	gd->countdown = (struct countdown*)malloc(sizeof(struct countdown));
	gd->countdown->hh = 0;
	gd->countdown->mm = 0;
	gd->countdown->ss = 0;
}

void gameDataDestroy(struct gameData* gd)
{
	characterDatabaseDestroy(&gd->characterDB);
	free(gd->ownFiveStarCharacters);
	free(gd->ownFourStarCharacters);

	free(gd->countdown);
}