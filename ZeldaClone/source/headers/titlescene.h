#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include <stdio.h>
#include "scene.h"
#include <SDL_mixer.h>


class TitleScene : public Scene
{
public:
	TitleScene(std::string path, Graphics& graphics);
	~TitleScene();

	void update(float elapsed);
	void draw(Graphics& graphics);
	void handleInput(SDL_Event& event);
	bool sceneSwitch();
	std::string nextScene();
	bool playerActive();
	bool hudActive();

private:

	// Scene Over?
	bool sceneDone;

	// Next Scene String ID
	std::string nextSc;

	// Texture
	SDL_Texture* tex;

	// Cutscene Phase
	int phase;

	// Title Screen
	SDL_Rect titleBase;

	// Title Screen Logo fade animation
	int fadeCounter;
	int fadeTrigger;
	int fadeIndex;

	// Splash 
	SDL_Rect splashBase;
	SDL_Rect splashDest;

	// Splash Screen animation
	int splashCounter;
	int splashTrigger;
	int splashIndex;

	// Waterfall
	SDL_Rect fallBase;
	std::vector<SDL_Rect> fallDst;
	int fallCounter;
	int fallTrigger;

	// Phase Counter
	int phaseCounter;
	int phaseTrigger;
	float texAlpha;

	// Scroll Rects
	std::vector<SDL_Rect> scrollSrc;
	std::vector<SDL_Rect> scrollDst;
	float scrollCounter;

	int scrollPauseCounter;
	int scrollPauseTrigger;
	bool pauseDone;

	void resetScroll();

	Mix_Music* music;

};

#endif