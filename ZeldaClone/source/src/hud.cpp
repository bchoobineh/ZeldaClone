#include "hud.h"

Hud::Hud(std::string path, Graphics& graphics)
{
	// Set Hud Params
	rubyCount = 0;
	bombCount = 0;
	keyCount = 0;
	lifeCount = 0;

	// Create Hud Texture
	tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path));

	// Set Hud Base
	hudBase = { 258, 11, 256, 56 };
	hudDst = { 0, 0, 256 * 4, 56 * 4 };

	// Set Number Base
	numBase = { 519, 117, 8, 8 };

	// Set Ruby, Bomb, and Key Destinations
	rubyDst = { 96 * 4, 16 * 4, 8 * 4, 8 * 4 };
	bombDst = { 96 * 4, 40 * 4, 8 * 4, 8 * 4 };
	keyDst = { 96 * 4, 32 * 4, 8 * 4, 8 * 4 };

	// Set Heart Source
	heartSrc = { 645, 117, 8, 8 };

	// Health Base
	healthBase = { 176 * 4, 32 * 4, 8 * 4, 8 * 4 };

	// Set Active Items
	selectedItem1 = { 0,0,0,0 };
	selectedItem2 = { 0,0,0,0 };

	// Set Item Destination
	item1Base = { 128*4, 24 * 4, 8 * 4, 16 * 4 };
	item2Base = { 152 * 4, 24 * 4, 8 * 4, 16 * 4 };

	// Setup Item Options
	itemOptions["bronzeSword"] = { 555, 137, 8, 16 };

}

Hud::~Hud()
{

}

void Hud::update(float elapsed, Player& player)
{
	rubyCount = player.getRubyCount();
	bombCount = player.getBombCount();
	keyCount = player.getKeyCount();
	lifeCount = player.getLifeCount();
}

void Hud::draw(Graphics& graphics)
{
	// Draw the Base
	graphics.drawTexture(tex, &hudBase, &hudDst);

	// Draw the Ruby, Bomb, and Key Count
	drawRubyCount(graphics);
	drawBombCount(graphics);
	drawKeyCount(graphics);

	// Draw Health
	drawHealth(graphics);

	// Draw Items
	drawItem1(graphics);
	drawItem2(graphics);
}

void Hud::drawRubyCount(Graphics& graphics)
{
	// Draw the X
	graphics.drawTexture(tex, &numBase, &rubyDst);
	
	if (rubyCount < 10)
	{
		SDL_Rect tmpDst = rubyDst;
		tmpDst.x += 32;

		SDL_Rect numSrc = numBase;
		numSrc.x += (9 * (rubyCount + 1));

		graphics.drawTexture(tex, &numSrc, &tmpDst);
	}
	else
	{
		// Write First Digit
		SDL_Rect tmpDst = rubyDst;
		tmpDst.x += 64;

		SDL_Rect numSrc = numBase;
		numSrc.x += (9 * ((rubyCount%10) + 1));

		graphics.drawTexture(tex, &numSrc, &tmpDst);

		// Second Digit;
		tmpDst.x -= 32;

		numSrc = numBase;
		numSrc.x += (9 * ((rubyCount/10) + 1));

		graphics.drawTexture(tex, &numSrc, &tmpDst);
	}


}

void Hud::drawBombCount(Graphics& graphics)
{
	graphics.drawTexture(tex, &numBase, &bombDst);

	if (bombCount < 10)
	{
		SDL_Rect tmpDst = bombDst;
		tmpDst.x += 32;

		SDL_Rect numSrc = numBase;
		numSrc.x += (9 * (bombCount + 1));

		graphics.drawTexture(tex, &numSrc, &tmpDst);
	}
	else
	{
		// Write First Digit
		SDL_Rect tmpDst = bombDst;
		tmpDst.x += 64;

		SDL_Rect numSrc = numBase;
		numSrc.x += (9 * ((bombCount % 10) + 1));

		graphics.drawTexture(tex, &numSrc, &tmpDst);

		// Second Digit;
		tmpDst.x -= 32;

		numSrc = numBase;
		numSrc.x += (9 * ((bombCount / 10) + 1));

		graphics.drawTexture(tex, &numSrc, &tmpDst);
	}

}

void Hud::drawKeyCount(Graphics& graphics)
{
	graphics.drawTexture(tex, &numBase, &keyDst);

	if (keyCount < 10)
	{
		SDL_Rect tmpDst = keyDst;
		tmpDst.x += 32;

		SDL_Rect numSrc = numBase;
		numSrc.x += (9 * (keyCount + 1));

		graphics.drawTexture(tex, &numSrc, &tmpDst);
	}
	else
	{
		// Write First Digit
		SDL_Rect tmpDst = keyDst;
		tmpDst.x += 64;

		SDL_Rect numSrc = numBase;
		numSrc.x += (9 * ((keyCount % 10) + 1));

		graphics.drawTexture(tex, &numSrc, &tmpDst);

		// Second Digit;
		tmpDst.x -= 32;

		numSrc = numBase;
		numSrc.x += (9 * ((keyCount / 10) + 1));

		graphics.drawTexture(tex, &numSrc, &tmpDst);
	}
}

void Hud::drawHealth(Graphics& graphics)
{
	SDL_Rect tmpDst = healthBase;
	for (int i = 0; i < lifeCount; i++)
	{
		graphics.drawTexture(tex, &heartSrc, &tmpDst);
		tmpDst.x += 32;
	}
}

void Hud::drawItem1(Graphics& graphics)
{
	// Valid Item
	if (selectedItem1.w >= 0)
	{
		graphics.drawTexture(tex, &itemOptions["bronzeSword"], &item1Base);
	}
}

void Hud::drawItem2(Graphics& graphics)
{
	// Valid Item
	if (selectedItem1.w > 0)
	{

	}
}