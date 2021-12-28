#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>

#include "globals.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	void drawScreen();
	void clearScreen();

	void drawTexture(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* dest);
	SDL_Surface* loadImage(std::string &path);

	SDL_Renderer* getRenderer() const;

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::map<std::string, SDL_Surface*> spriteSheets;

};

#endif