#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "globals.h"

class Rectangle
{
public:
	Rectangle();
	Rectangle(int x, int y, int w, int h);
	~Rectangle();

	const int getLeft() const;
	const int getRight() const;
	const int getTop() const;
	const int getBot() const;
	const int getWidth() const;
	const int getHeight() const;
	const int getCenterX() const;
	const int getCenterY() const;


	const bool inCollision(const Rectangle& rect) const;

private:
	int xPos, yPos, width, height;
};

#endif