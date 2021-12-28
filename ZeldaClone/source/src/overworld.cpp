#include "overworld.h"

Overworld::Overworld(std::string path, Graphics& graphics) :
	Scene(path, graphics)
{
	// Offset position by screen
	for (int i = 0; i < tiles.size(); i++)
	{
		Vector2 loc = tiles.at(i).getPosition();
		tiles.at(i).setPosition(Vector2(loc.x, loc.y + 56));
	}


}

Overworld::~Overworld()
{}

void Overworld::update(float elapsed) 
{}

void Overworld::draw(Graphics& graphics)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles.at(i).draw(graphics, 4);
	}

}

void Overworld::handleInput(SDL_Event& event)
{}

bool Overworld::sceneSwitch()
{
	return false;
}

std::string Overworld::nextScene()
{
	return "TEMP";
}

bool Overworld::playerActive()
{
	return true;
}

bool Overworld::hudActive()
{
	return true;
}

