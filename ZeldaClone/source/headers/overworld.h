#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "scene.h"
#include "rectangle.h"
#include <vector>

class Overworld : public Scene
{
public:
	Overworld(std::string path, Graphics& graphics);
	~Overworld();

	void update(float elapsed);
	void draw(Graphics& graphics);
	void handleInput(SDL_Event& event);
	bool sceneSwitch();
	std::string nextScene();
	bool playerActive();
	bool hudActive();

private:

};

#endif