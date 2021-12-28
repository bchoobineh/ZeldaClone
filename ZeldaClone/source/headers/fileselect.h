#ifndef FILE_SELECT_H
#define FILE_SELECT_H

#include "scene.h"

struct playerProfile
{
	std::vector<Vector2> name;
	int rubyCount;
	int lifeCount;
};

class FileSelect : public Scene
{
public:
	FileSelect(std::string path, Graphics& graphics);
	~FileSelect();

	void update(float elapsed);
	void draw(Graphics& graphics);
	void handleInput(SDL_Event& event);
	bool sceneSwitch();
	std::string nextScene();
	bool playerActive();
	bool hudActive();


private:

	// File Select Texture
	SDL_Texture* tex;

	bool sceneDone;

	// Player Profiles
	std::vector<playerProfile> profiles;
	int profileIndex;

	// Screen Number
	int screenNum;
	
	// Base Backdrops
	SDL_Rect selectSrc;
	SDL_Rect registerSrc;

	// Screen 1 Name Base
	SDL_Rect sc1NameBase;
	SDL_Rect rubyBase;
	SDL_Rect lifeBase;

	// Screen 2 Flash Src
	SDL_Rect flashSrc;
	SDL_Rect flashBase;
	SDL_Rect flashCurrent;

	SDL_Rect nameFlashBase;
	SDL_Rect nameFlashCurrent;
	Vector2 nameFlashLoc;

	bool flashTrigger;
	float flashCounter;

	// Link Sprite
	SDL_Rect linkSrc;
	SDL_Rect linkDstBase;

	// Number Base
	SDL_Rect numBase;

	std::vector<SDL_Rect> heartLoc;
	std::vector<SDL_Rect> heartLoc2;
	SDL_Rect heartSrc;
	int heartIndex;

	void drawScreen1(Graphics& graphics);
	void drawScreen2(Graphics& graphics);

	void addLetter();
	void drawName(std::vector<Vector2> name, SDL_Rect base, Graphics &graphics);

};


#endif