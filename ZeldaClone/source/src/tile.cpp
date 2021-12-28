#include "tile.h"

Tile::Tile()
{
	size = Vector2(0, 0);
	position = Vector2(0, 0);
	sheetPosition = Vector2(0, 0);
	spriteSheet = NULL;
}

Tile::Tile(SDL_Texture* sheet, Vector2 size, Vector2 sheetPosition, Vector2 position) :
	spriteSheet(sheet),
	size(size),
	sheetPosition(sheetPosition),
	position(position)
{}

Tile::~Tile()
{}

void Tile::update(int elapsed)
{}

void Tile::draw(Graphics &graphics, int spriteScale)
{
	SDL_Rect dest = { spriteScale * position.x, spriteScale * position.y, size.x * spriteScale, size.y * spriteScale };
	SDL_Rect src = { sheetPosition.x, sheetPosition.y, size.x, size.y };

	graphics.drawTexture(spriteSheet, &src, &dest);
}

SDL_Texture* Tile::getTexture()
{
	return spriteSheet;
}

Vector2 Tile::getPosition()
{
	return position;
}

void Tile::setPosition(Vector2 pos)
{
	position.x = pos.x;
	position.y = pos.y;
}
