#include "animSprite.h"

AnimSprite::AnimSprite()
{
	frameNum = 0;
	updateTime = 0.0f;
	animOnce = false;
	currentAnim = "";
	active = false;
}

AnimSprite::AnimSprite(Graphics& graphics, std::string path, int srcX, int srcY, int width, int height, float posX, float posY, float updateTime):
	Sprite(graphics, path, srcX, srcY, width, height, posX, posY)
{
	frameNum = 0;
	this->updateTime = updateTime;
	animOnce = false;
	currentAnim = "";
	active = true;

}

AnimSprite::~AnimSprite()
{}

void AnimSprite::update(int elapsed)
{
	Sprite::update();

	elapsedTime += elapsed;
	if (elapsedTime > updateTime)
	{
		elapsedTime -= updateTime;
		if (frameNum < animations[currentAnim].size() - 1)
		{
			frameNum++;
		}
		else
		{
			if (animOnce)
			{

			}
			stopAnimation();
		}
	}

}

void AnimSprite::draw(Graphics& graphics, int x, int y)
{
	// Only draw if Active
	if (active)
	{
		SDL_Rect dst;
		dst.x = x + offsets[currentAnim].x;
		dst.y = y + offsets[currentAnim].y;
		dst.w = source.w * 4;
		dst.h = source.h * 4;

		SDL_Rect src = animations[currentAnim][frameNum];
		graphics.drawTexture(tex, &src, &dst);
	}
}


void AnimSprite::addAnimation(int numFrames, int x, int y, std::string name, int width, int height, Vector2 offset)
{
	std::vector<SDL_Rect> r;
	for (int i = 0; i < numFrames; i++)
	{
		SDL_Rect tmp = { (i + x) * width, y, width, height };
		r.push_back(tmp);
	}

	animations[name] = r;
	offsets[name] = offset;
}

void AnimSprite::resetAnimList()
{
	animations.clear();
	offsets.clear();
}

void AnimSprite::playAnim(std::string animName, bool once)
{
	animOnce = once;
	
	// Don't repeat if already running
	if (currentAnim != animName)
	{
		currentAnim = animName;
		frameNum = 0;
	}
}

void AnimSprite::stopAnimation()
{
	frameNum = 0;
	animationDone(currentAnim);
}

void AnimSprite::setVisible(bool visible)
{
	active = visible;
}

