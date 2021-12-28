#ifndef ANIM_SPRITE_H
#define ANIM_SPRITE_H


#include "sprite.h"

class AnimSprite : public Sprite
{
public:
	AnimSprite();
	AnimSprite(Graphics& graphics, std::string path, int srcX, int srcY, int width, int height, float posX, float posY, float updateTime);
	~AnimSprite();

	void playAnim(std::string animName, bool once = false);

	void update(int elapsed);

	void draw(Graphics& graphics, int x, int y);


protected:
	std::string currentAnim;
	bool animOnce;
	double updateTime;

	void addAnimation(int numFrames, int x, int y, std::string name, int width, int height, Vector2 offset);

	void resetAnimList();

	void stopAnimation();

	void setVisible(bool visible);

	virtual void animationDone(std::string animName) = 0;

	virtual void setupAnimations() = 0;


private:
	std::map<std::string, std::vector<SDL_Rect>> animations;
	std::map<std::string, Vector2> offsets;

	int frameNum;
	double elapsedTime;
	bool active;



};

#endif