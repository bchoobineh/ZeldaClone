#ifndef GLOBALS_H
#define GLOBALS_H

#include <algorithm>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 896
#define SCREEN_TITLE "Zelda NES Clone"

#define FPS 60
#define FRAME_TIME_MAX 1000/FPS


struct Vector2
{
	int x, y;
	Vector2() :
		x(0), y(0)
	{}

	Vector2(int x, int y) :
		x(x), y(y)
	{}
};



#endif