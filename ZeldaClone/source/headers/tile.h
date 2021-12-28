#ifndef TILE_H
#define TILE_H

#include "graphics.h"

class Tile
{
public:
	Tile();
	Tile(SDL_Texture* sheet, Vector2 size, Vector2 sheetPosition, Vector2 position);
	~Tile();
	void update(int elapsed);
	void draw(Graphics& graphics, int spriteScale);

	SDL_Texture* getTexture();

	Vector2 getPosition();
	void setPosition(Vector2 pos);

protected:	
	SDL_Texture* spriteSheet;
	Vector2 size;
	Vector2 position;
	Vector2 sheetPosition;

};

#endif