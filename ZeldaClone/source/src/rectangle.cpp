#include "rectangle.h"

Rectangle::Rectangle()
{
	xPos = 0.0f;
	yPos = 0.0f;
	width = 0.0f;
	height = 0.0f;
}

Rectangle::Rectangle(int x, int y, int w, int h)
{
	xPos = x;
	yPos = y;
	width = w;
	height = h;
}

Rectangle::~Rectangle()
{}

const int Rectangle::getLeft() const
{
	return xPos;
}

const int Rectangle::getRight() const
{
	return (xPos + width);
}

const int Rectangle::getTop() const
{
	return yPos;
}

const int Rectangle::getBot() const
{
	return (yPos + height);
}

const int Rectangle::getWidth() const
{
	return width;
}

const int Rectangle::getHeight() const
{
	return height;
}

const int Rectangle::getCenterX() const
{
	return (xPos + (width / 2));
}

const int Rectangle::getCenterY() const
{
	return (yPos + (height / 2));
}

const bool Rectangle::inCollision(const Rectangle& rect) const
{
	return((getRight() >= rect.getLeft()) && (getLeft() <= rect.getRight()) && (getTop() <= rect.getBot()) && (getBot() >= rect.getTop()));
}

