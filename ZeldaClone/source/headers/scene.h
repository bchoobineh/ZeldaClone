#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include <string>

#include "graphics.h"
#include "tile.h"
#include "rectangle.h"

struct Tileset 
{
	SDL_Texture* tex;
	int fGID;

	Tileset() 
	{
		tex = NULL;
		fGID = -1;
	}
	Tileset(SDL_Texture* texture, int firstGid) 
	{
		tex = texture;
		fGID = firstGid;
	}
};

class Scene
{

public:
	Scene();
	Scene(std::string path, Graphics& graphics);
	~Scene();

	virtual void update(float elapsed) = 0;
	virtual void draw(Graphics& graphics) = 0;
	virtual void handleInput(SDL_Event& event) = 0;
	virtual bool sceneSwitch() = 0;
	virtual std::string nextScene() = 0;
	virtual bool playerActive() = 0;

	virtual bool hudActive() = 0;

	std::vector<Rectangle> checkRectCollisions(const Rectangle& rect);

protected:
	
	Vector2 sceneSize;
	Vector2 tileSize;

	std::vector<Tile> tiles;
	std::vector<Tileset> tilesets;
	std::vector<Rectangle> collisions;


	void loadMap(std::string path, Graphics &graphics);


};





#endif