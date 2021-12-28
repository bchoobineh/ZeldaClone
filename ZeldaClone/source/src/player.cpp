#include "player.h"

namespace link_constants
{
	const float WALK_SPEED = 0.2f;
}


Player::Player()
{
	bombCount = 0;
	rubyCount = 0;
	keyCount = 0;
	lifeCount = 3;

	deltaX = 0.0f;
	deltaY = 0.0f;
	prevFace = Face::BOT;
}

Player::Player(Graphics& graphics, Vector2 spawnLocation):
	AnimSprite(graphics, "tilesets/linkCard2.png", 0, 0, 16, 16, spawnLocation.x, spawnLocation.y, 300)
{
	deltaX = 0.0f;
	deltaY = 0.0f;

	bombCount = 0;
	rubyCount = 0;
	keyCount = 0;
	lifeCount = 3;

	prevFace = Face::BOT;


	std::string tmp = "tilesets/linkCard2.png";
	graphics.loadImage(tmp);

	setupAnimations();
	playAnim("RunDown");
}

Player::~Player()
{}

void Player::draw(Graphics& graphics)
{
	AnimSprite::draw(graphics, xPos, yPos);
}

void Player::update(float elapsed)
{
	xPos += deltaX * elapsed;
	yPos += deltaY * elapsed;

	AnimSprite::update(elapsed);

	prevFace = getCurrentFace();

	// Go Idle
	if (deltaX == 0 && deltaY == 0)
	{
		if (prevFace == TOP)
			playAnim("IdleTop");
		else if (prevFace == BOT)
			playAnim("IdleBot");
		else if (prevFace == RIGHT)
			playAnim("IdleRight");
		else
			playAnim("IdleLeft");
	}

}

void Player::animationDone(std::string animName)
{}

void Player::setupAnimations()
{
	addAnimation(1, 0, 0, "IdleBot", 16, 16, Vector2(0, 0));	
	addAnimation(2, 0, 0, "RunDown", 16, 16, Vector2(0, 0));

	addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
	addAnimation(2, 0, 16, "RunRight", 16, 16, Vector2(0, 0));

	addAnimation(1, 0, 32, "IdleTop", 16, 16, Vector2(0, 0));
	addAnimation(2, 0, 32, "RunUp", 16, 16, Vector2(0, 0));

	addAnimation(1, 0, 48, "IdleLeft", 16, 16, Vector2(0, 0));
	addAnimation(2, 0, 48, "RunLeft", 16, 16, Vector2(0, 0));
}

int Player::getRubyCount()
{
	return rubyCount;
}

int Player::getBombCount()
{
	return bombCount;
}

int Player::getKeyCount()
{
	return keyCount;
}

int Player::getLifeCount()
{
	return lifeCount;
}

void Player::handleInput(SDL_Event& event)
{
	// Released Key
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.scancode == SDL_SCANCODE_UP)
		{
			deltaY = 0;
		}

		if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
			deltaY = 0;
		}

		if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			deltaX = 0;
		}

		if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
			deltaX = 0;
		}
	}

	// Pressed Key
	else if (event.type == SDL_KEYDOWN)
	{

		if (event.key.keysym.scancode == SDL_SCANCODE_UP)
		{
			if(deltaX == 0)
				playAnim("RunUp");


			deltaY = -link_constants::WALK_SPEED;
		}

		if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
			if (deltaX == 0)
				playAnim("RunDown");

			deltaY = link_constants::WALK_SPEED;
		}

		if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			if (deltaY == 0)
				playAnim("RunRight");

			deltaX = link_constants::WALK_SPEED;
		}

		if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
			if (deltaY == 0)
				playAnim("RunLeft");
			deltaX = -link_constants::WALK_SPEED;
		}

	}

}

Face Player::getCurrentFace()
{
	if (deltaY > 0)
	{
		return Face::BOT;
	}
	else if (deltaY < 0)
	{
		return Face::TOP;
	}
	else
	{
		if (deltaX < 0)
		{
			return Face::LEFT;
		}
		else if (deltaX > 0)
		{
			return Face::RIGHT;
		}
		else
			return prevFace;
	}
}

void Player::handleRectCollisions(std::vector<Rectangle>& rects)
{
	for (int i = 0; i < rects.size(); i++)
	{
		Side collisionSide = Sprite::getCollisionSide(rects.at(i));
		
		switch (collisionSide)
		{
		case Side::TOP_SIDE:
			deltaY = 0;
			yPos = rects.at(i).getBot() + 1;
			break;

		case Side::BOT_SIDE:
			yPos = rects.at(i).getTop() - boundingBox.getHeight() - 1;
			deltaY = 0;
			break;

		case Side::LEFT_SIDE:
			xPos = rects.at(i).getRight() + 1;
			break;

		case Side::RIGHT_SIDE:
			xPos = rects.at(i).getLeft() - boundingBox.getWidth() - 1;
			break;



		}

	}
}