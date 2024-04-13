#include"characterDatabase.h"

void characterDatabaseInit(characterDatabase*cd)
{
	vectorInit(&cd->vecFiveStarCharacterImg);
	vectorInit(&cd->vecFiveStarCharacterMask);
	vectorInit(&cd->vecFourStarCharacterImg);
	vectorInit(&cd->vecFourStarCharacterMask);

	char imgPath[50];
	char maskPath[50];

	IMAGE* imgFiveArr[FIVE_STAR_CHARACTERNUM];
	IMAGE* maskFiveArr[FIVE_STAR_CHARACTERNUM];
	for (int i = 0; i < FIVE_STAR_CHARACTERNUM; i++) {
		imgFiveArr[i] = new IMAGE;
		maskFiveArr[i] = new IMAGE;
		sprintf(imgPath, "asset/characters/fiveStar/%s.png", cd->fiveStarCharacterName[i]);
		sprintf(maskPath, "asset/characters/fiveStar/%s_mask.png", cd->fiveStarCharacterName[i]);
		loadimage(imgFiveArr[i], imgPath);
		loadimage(maskFiveArr[i], maskPath);
		cd->vecFiveStarCharacterImg.append(&cd->vecFiveStarCharacterImg, imgFiveArr[i]);
		cd->vecFiveStarCharacterMask.append(&cd->vecFiveStarCharacterMask, maskFiveArr[i]);
	}
	IMAGE* imgFourArr[FOUR_STAR_CHARACTERNUM];
	IMAGE* maskFourArr[FOUR_STAR_CHARACTERNUM];
	for (int i = 0; i < FOUR_STAR_CHARACTERNUM; i++) {
		imgFourArr[i] = new IMAGE;
		maskFourArr[i] = new IMAGE;
		sprintf(imgPath, "asset/characters/fourStar/%s.png", cd->fourStarCharacterName[i]);
		sprintf(maskPath, "asset/characters/fourStar/%s_mask.png", cd->fourStarCharacterName[i]);
		loadimage(imgFourArr[i], imgPath);
		loadimage(maskFourArr[i], maskPath);
		cd->vecFourStarCharacterImg.append(&cd->vecFourStarCharacterImg, imgFourArr[i]);
		cd->vecFourStarCharacterMask.append(&cd->vecFourStarCharacterMask, maskFourArr[i]);
	}
}

void characterDatabaseDestroy(characterDatabase*cd)
{
	IMAGE* img;
	IMAGE* mask;
	for (int i = 0; i < FIVE_STAR_CHARACTERNUM; i++) {
		img = (IMAGE*)cd->vecFiveStarCharacterImg.get(&cd->vecFiveStarCharacterImg, i);
		mask = (IMAGE*)cd->vecFiveStarCharacterMask.get(&cd->vecFiveStarCharacterMask, i);
		delete img;
		delete mask;
	}
	for (int i = 0; i < FOUR_STAR_CHARACTERNUM; i++) {
		img = (IMAGE*)cd->vecFourStarCharacterImg.get(&cd->vecFourStarCharacterImg, i);
		mask = (IMAGE*)cd->vecFourStarCharacterMask.get(&cd->vecFourStarCharacterMask, i);
		delete img;
		delete mask;
	}
	vectorDestroy(&cd->vecFiveStarCharacterImg);
	vectorDestroy(&cd->vecFiveStarCharacterMask);
	vectorDestroy(&cd->vecFourStarCharacterImg);
	vectorDestroy(&cd->vecFourStarCharacterMask);
}