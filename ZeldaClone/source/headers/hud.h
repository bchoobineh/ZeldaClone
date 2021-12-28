#ifndef HUD_H
#define HUD_H

#include "graphics.h"
#include "player.h"

class Hud
{
public:
	Hud(std::string path, Graphics& graphics);
	~Hud();

	void update(float elapsed, Player& player);
	void draw(Graphics& graphics);


private:

	// Texture
	SDL_Texture* tex;

	// Hud Location
	SDL_Rect hudBase;
	SDL_Rect hudDst;

	// Number Base
	SDL_Rect numBase;
	SDL_Rect rubyDst;
	SDL_Rect bombDst;
	SDL_Rect keyDst;

	// Heart Src
	SDL_Rect heartSrc;
	
	// Health Location
	SDL_Rect healthBase;

	// Item 1 and Item 2 Base
	SDL_Rect item1Base;
	SDL_Rect item2Base;

	// Selected Item 1 and Item 2
	SDL_Rect selectedItem1;
	SDL_Rect selectedItem2;

	// Mapping of Items
	std::map<std::string, SDL_Rect> itemOptions;

	int rubyCount;
	int bombCount;
	int keyCount;
	int lifeCount;

	void drawRubyCount(Graphics& graphics);
	void drawBombCount(Graphics& graphics);
	void drawKeyCount(Graphics& graphics);
	void drawHealth(Graphics& graphics);

	void drawItem1(Graphics& graphics);
	void drawItem2(Graphics& graphics);




};

#endif