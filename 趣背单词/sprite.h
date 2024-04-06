#pragma once

struct sprite {
	void (*draw)(struct sprite*);
	void (*update)(struct sprite*);

	int x;
	int y;

	int width;
	int height;
};