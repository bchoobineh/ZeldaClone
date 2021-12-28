#include "graphics.h"

Graphics::Graphics()
{
	// Create SDL Window and Renderer
	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) != 0)
	{
		printf("SDL Window and Renderer creation failed!\n");
		exit(1);
	}
	printf("SDL Window and Renderer Initialized...\n");

	// Set the Title
	SDL_SetWindowTitle(window, SCREEN_TITLE);
}

Graphics::~Graphics()
{
	// Free any sprite sheet surfaces
	std::map<std::string, SDL_Surface*>::iterator iter;
	for (iter = spriteSheets.begin(); iter != spriteSheets.end(); iter++)
		SDL_FreeSurface(iter->second);

	// Destroy Window and Renderer
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Graphics::drawScreen()
{
	SDL_RenderPresent(renderer);
}

void Graphics::clearScreen()
{
	SDL_RenderClear(renderer);
}

void Graphics::drawTexture(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* dest)
{
	SDL_RenderCopy(renderer, texture, source, dest);
}

SDL_Surface* Graphics::loadImage(std::string& path)
{
	// If sprite sheet not loaded yet, load it in
	if (spriteSheets.count(path) == 0)
		spriteSheets[path] = IMG_Load(path.c_str());
	
	return spriteSheets[path];
}

SDL_Renderer* Graphics::getRenderer() const
{
	return renderer;
}