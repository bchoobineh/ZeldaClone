#ifndef SPRITE_H
#define SPRITE_H

#include "graphics.h"
#include "rectangle.h"

enum Side
{
	TOP_SIDE,
	BOT_SIDE,
	LEFT_SIDE,
	RIGHT_SIDE
};

class Sprite
{
public:
	Sprite();
	Sprite(Graphics& graphics, std::string path, int srcX, int srcY, int width, int height, float posX, float posY);
	~Sprite();

	virtual void update();
	void draw(Graphics& graphics, int x, int y);

	float getXPosition();
	float getYPosition();

	const Side getCollisionSide(Rectangle& rect) const;

	const Rectangle getBoundingBox() const;

protected:
	float xPos, yPos;
	SDL_Texture* tex;
	SDL_Rect source;
	Rectangle boundingBox;

};

#endif