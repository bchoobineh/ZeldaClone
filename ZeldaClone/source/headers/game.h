#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "graphics.h"
#include "scene.h"
#include "titlescene.h"
#include "fileselect.h"
#include "overworld.h"
#include "hud.h"
#include "player.h"

class Game
{
public:
	Game();
	~Game();

	void start();

private:	
	void handleEvents();
	void update(float elapsed);
	void draw();

	// Graphics Engine
	Graphics graphics; 

	// Active Scene
	TitleScene* intro;
	FileSelect* fileSel;
	Overworld* overworld;
	Hud* hud;
	Player player;

	std::map<std::string, Scene*> sceneStorage;
	Scene* activeScene;

	bool running;
	bool hudActive;
	bool playerActive;

};

#endif;