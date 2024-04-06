#include"characterDatabase.h"

void characterDatabaseInit(characterDatabase*cd)
{
	vectorInit(&cd->vecFiveStarCharacterImg);
	vectorInit(&cd->vecFiveStarCharacterMask);
	vectorInit(&cd->vecFourStarCharacterImg);
	vectorInit(&cd->vecFourStarCharacterMask);

	char imgPath[50];
	char maskPath[50];

	IMAGE* imgFiveArr[FIVESTARCHARACTERNUM];
	IMAGE* maskFiveArr[FIVESTARCHARACTERNUM];
	for (int i = 0; i < FIVESTARCHARACTERNUM; i++) {
		imgFiveArr[i] = new IMAGE;
		maskFiveArr[i] = new IMAGE;
		sprintf(imgPath, "asset/image/characters/fiveStar/%s.png", cd->fiveStarCharacterName[i]);
		sprintf(maskPath, "asset/image/characters/fiveStar/%s_mask.png", cd->fiveStarCharacterName[i]);
		loadimage(imgFiveArr[i], imgPath);
		loadimage(maskFiveArr[i], maskPath);
		cd->vecFiveStarCharacterImg.append(&cd->vecFiveStarCharacterImg, imgFiveArr[i]);
		cd->vecFiveStarCharacterMask.append(&cd->vecFiveStarCharacterMask, maskFiveArr[i]);
	}
	IMAGE* imgFourArr[FOURSTARCHARACTERNUM];
	IMAGE* maskFourArr[FOURSTARCHARACTERNUM];
	for (int i = 0; i < FOURSTARCHARACTERNUM; i++) {
		imgFourArr[i] = new IMAGE;
		maskFourArr[i] = new IMAGE;
		sprintf(imgPath, "asset/image/characters/fourStar/%s.png", cd->fourStarCharacterName[i]);
		sprintf(maskPath, "asset/image/characters/fourStar/%s_mask.png", cd->fourStarCharacterName[i]);
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
	for (int i = 0; i < FIVESTARCHARACTERNUM; i++) {
		img = (IMAGE*)cd->vecFiveStarCharacterImg.get(&cd->vecFiveStarCharacterImg, i);
		mask = (IMAGE*)cd->vecFiveStarCharacterMask.get(&cd->vecFiveStarCharacterMask, i);
		delete img;
		delete mask;
	}
	for (int i = 0; i < FOURSTARCHARACTERNUM; i++) {
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