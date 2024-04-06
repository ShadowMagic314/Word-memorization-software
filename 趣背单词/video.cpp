#include"video.h"

void videoPlay(struct video* v)
{
	char command[100];
	LARGE_INTEGER startCount, endCount, F;
	QueryPerformanceFrequency(&F);

	for (int i = 0; i < v->imgsCnt; i++) {
		QueryPerformanceCounter(&startCount);
		cleardevice();
		//
		sprintf(command, "%s/Image%d.jpg", v->imgsPath, i + 1);
		loadimage(v->imgTmp, command);
		putimage(0, 0, v->imgTmp);
		if (i == 0) {
			sprintf(command, "open %s", v->soundPath);
			mciSendString(command, NULL, 0, NULL);
			sprintf(command, "play %s", v->soundPath);
			mciSendString(command, NULL, 0, NULL);
		}
		else if (i == v->imgsCnt-1) {
			sprintf(command, "close %s", v->soundPath);
			mciSendString(command, NULL, 0, NULL);
		}
		//
		FlushBatchDraw();
		QueryPerformanceCounter(&endCount);
		long long elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		while (elapse < 1000000 / v->fps) {
			Sleep(1);
			QueryPerformanceCounter(&endCount);
			elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		}
	}
}

void videoInit(struct video* v, const char imgsPath[100], const char soundPath[100], const int imgsCnt, const int fps)
{
	v->play = (void (*)(struct video*))videoPlay;

	strcpy(v->imgsPath, imgsPath);
	strcpy(v->soundPath, soundPath);
	v->imgsCnt = imgsCnt;

	v->imgTmp = new IMAGE;

	v->fps = fps;
}

void videoDestroy(struct video* v)
{
	delete v->imgTmp;
}