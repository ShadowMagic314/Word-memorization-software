#include"gameloop.h"

void gameLoop(struct scene* s, int fps, struct gameData* gd)
{
	timeBeginPeriod(1);
	LARGE_INTEGER startCount, endCount, F;
	QueryPerformanceFrequency(&F);

	BeginBatchDraw();
	while (1)
	{
		QueryPerformanceCounter(&startCount);
		cleardevice();

		s->update(s, gd);
		s->draw(s,gd);

		if (s->isQuit(s,gd)) {
			break;
		}
		FlushBatchDraw();
		QueryPerformanceCounter(&endCount);
		long long elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		while (elapse < 1000000 / fps) {
			Sleep(1);
			ExMessage msg;
			if (peekmessage(&msg, EX_MOUSE)) {
				s->control(s, &msg,gd);
			}
			QueryPerformanceCounter(&endCount);
			elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		}
	}
	EndBatchDraw();
	timeEndPeriod(1);
}