#include"bkMusic.h"

void bkMusic(struct gameData* gd)
{
	if (gd->isbkMusic == true) {
		mciSendString("open asset/sounds/bkMusic/bkMusic.wma", NULL, 0, NULL);
		mciSendString("play asset/sounds/bkMusic/bkMusic.wma repeat", NULL, 0, NULL);
	}
	if (gd->isbkMusic == false) {
		mciSendString("close asset/sounds/bkMusic/bkMusic.wma", NULL, 0, NULL);
	}
}