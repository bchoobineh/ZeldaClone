#include "sprite.h"

Sprite::Sprite()
{
	xPos = 0;
	yPos = 0;
}

Sprite::Sprite(Graphics& graphics, std::string path, int srcX, int srcY, int width, int height, float posX, float posY)
{
	// Create Sprite Texture
	tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path));

	// Setup Sprite Location
	xPos = posX;
	yPos = posY;

	// Set Source Rectangle
	source.x = srcX;
	source.y = srcY;
	source.w = width;
	source.h = height;

	// Setup bounding box
	boundingBox = Rectangle(xPos, yPos, 4 * width, 4 * height);
}

Sprite::~Sprite()
{

}

void Sprite::update()
{
	boundingBox = Rectangle(xPos, yPos, 4 *source.w, 4 * source.h);
}

void Sprite::draw(Graphics& graphics, int x, int y)
{
	SDL_Rect dst = { x, y, source.w * 4, source.h * 4};
	graphics.drawTexture(tex, &source, &dst);
}

float Sprite::getXPosition()
{
	return xPos;
}

float Sprite::getYPosition()
{
	return yPos;
}

const Rectangle Sprite::getBoundingBox() const
{
	return boundingBox;
}

const Side Sprite::getCollisionSide(Rectangle& rect) const
{
	int numRight, numLeft, numTop, numBot;
	numRight = getBoundingBox().getRight() - rect.getLeft();
	numLeft = rect.getRight() - getBoundingBox().getLeft();
	numTop = rect.getBot() - getBoundingBox().getTop();
	numBot = getBoundingBox().getBot() - rect.getTop();

	// Find smallest
	int tmp[4] = { abs(numRight), abs(numLeft), abs(numTop), abs(numBot) };
	int smallest = tmp[0];
	for (int i = 0; i < 4; i++)
		if (tmp[i] < smallest)
			smallest = tmp[i];

	// Return side based on smallest
	return

		smallest == abs(numRight) ? Side::RIGHT_SIDE :
		smallest == abs(numLeft) ? Side::LEFT_SIDE :
		smallest == abs(numTop) ? Side::TOP_SIDE :
		Side::BOT_SIDE;


}