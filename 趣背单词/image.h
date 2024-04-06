#pragma once
#include<easyx.h>
#include <graphics.h>
#include <conio.h>
#include<stdio.h>
#pragma comment( lib, "MSIMG32.LIB")

void putTransparentImage_mask(int x, int y, const IMAGE* mask, const IMAGE* img);
void putTransparentImage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);