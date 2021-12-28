#include <stdio.h>

#include "game.h"


Game::Game()
{

	// Initialize the SDL Library
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL Initialization Failed!\n");
		exit(1);
	}
	printf("SDL Initialization Complete...\n");

	// Hud not active yet
	hudActive = false;
	playerActive = false;

	// Game not running....yet
	running = false;

	intro = new TitleScene("tilesets/titleCard.png", graphics);

	fileSel = new FileSelect("tilesets/fileCard.png", graphics);

	overworld = new Overworld("maps/overworldMap.tmx", graphics);

	hud = new Hud("tilesets/hud.png", graphics);

	sceneStorage["Title"] = intro;
	sceneStorage["FileSelect"] = fileSel;
	sceneStorage["Overworld"] = overworld;

	activeScene = sceneStorage["Title"];
}

Game::~Game()
{
	SDL_Quit();
	printf("SDL Cleaned Up...\n");
}

void Game::start()
{
	// Game started running
	running = true;

	// The last time we updated
	int lastUpdate = SDL_GetTicks();

	// Create Player
	player = Player(graphics, Vector2(600, 600));

	while (running)
	{
		// Handle user input
		handleEvents();

		// Handle FPS and Update the game		
		int currentTime = SDL_GetTicks();
		int elapsed = currentTime - lastUpdate;		
		update(std::min(elapsed, FRAME_TIME_MAX));
		lastUpdate = currentTime;

		// Draw the game
		draw();
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			running = false;
			break;
			
		case SDL_KEYDOWN:
		{
			activeScene->handleInput(event);
			if (playerActive)
				player.handleInput(event);
		}
		break;

		case SDL_KEYUP:
		{
			if (playerActive)
				player.handleInput(event);
		}
		break;
	
	}
}

void Game::update(float elapsed)
{
	// Check Hud Status
	hudActive = activeScene->hudActive();

	// Check Player Status
	playerActive = activeScene->playerActive();

	// If we are switching scenes
	if (activeScene->sceneSwitch())
	{
		activeScene = sceneStorage[activeScene->nextScene()];
	}
	else
	{
		activeScene->update(elapsed);
	}

	// Update HUD
	if (hudActive)
		hud->update(elapsed, player);

	//if (playerActive)
	if(playerActive)
		player.update(elapsed);

	
	// Check for Collisions
	std::vector<Rectangle> colliders;
	if ((colliders = activeScene->checkRectCollisions(player.getBoundingBox())).size() > 0)
	{
		player.handleRectCollisions(colliders);
	}
	
}

void Game::draw()
{
	// Clear the current screen
	graphics.clearScreen();

	// Draw the Level
	activeScene->draw(graphics);

	// Draw HUD if active
	if (hudActive)
		hud->draw(graphics);

	if (playerActive)
	{
		player.draw(graphics);
	}

	// Render the current screen
	graphics.drawScreen();
}