#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include<easyx.h>
#include<string.h>
#include<stdio.h>

struct video {
	void (*play)(struct video*);

	char imgsPath[100];
	char soundPath[100];
	int imgsCnt;
	int fps;

	IMAGE *imgTmp;
};

void videoInit(struct video*, const char imgsPath[100], const char soundPath[100], const int imgsCnt, const int fps);
void videoDestroy(struct video* v);