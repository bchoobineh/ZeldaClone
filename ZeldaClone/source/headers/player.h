#ifndef PLAYER_H
#define PLAYER_H

#include "animSprite.h"

enum Face
{
	TOP,
	BOT,
	LEFT,
	RIGHT
};

class Player : public AnimSprite
{
public:
	Player();
	Player(Graphics& graphics, Vector2 spawnLocation);
	~Player();

	void draw(Graphics& graphics);

	void update(float elapsed);

	virtual void animationDone(std::string animName);
	virtual void setupAnimations();

	int getRubyCount();
	int getBombCount();
	int getKeyCount();
	int getLifeCount();

	void handleInput(SDL_Event& event);

	Face getCurrentFace();

	void handleRectCollisions(std::vector<Rectangle>& rects);

private:
	float deltaX, deltaY;

	int rubyCount;
	int bombCount;
	int keyCount;
	int lifeCount;
	Face prevFace;

};

#endif