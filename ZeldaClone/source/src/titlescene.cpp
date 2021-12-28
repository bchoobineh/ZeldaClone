#include "titlescene.h"

TitleScene::TitleScene(std::string path, Graphics& graphics)
{
	// Scene not done yet
	sceneDone = false;

	// Next Scene name
	nextSc = "FileSelect";

	// Create Texture
	tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path));

	// Start in cutscene phase 1
	phase = 0;

	// Title Card base location
	titleBase = { 0, 0, 256, 224 };
	fadeTrigger = 200;
	fadeCounter = fadeTrigger;
	fadeIndex = 0;

	// Splash base
	splashBase = { 96, 672, 32, 16 };
	splashDest = { 320, 640, 128, 64 };
	splashTrigger = 100;
	splashCounter = splashTrigger;
	splashIndex = 0;

	// Waterfall
	fallBase = { 0, 672, 32, 16 };
	fallDst.push_back({ 320, 700, 128, 64 });
	fallDst.push_back({ 320, 770, 128, 64 });
	fallDst.push_back({ 320, 840, 128, 64 });

	fallTrigger = 4;
	fallCounter = fallTrigger;

	// Phase Change
	phaseTrigger = 8000;
	phaseCounter = phaseTrigger;
	texAlpha = 255.0f;

	// Get Scroll Source
	scrollSrc.push_back({ 0, 224, 256, 224 });
	scrollSrc.push_back({ 256, 224, 256, 224 });
	scrollSrc.push_back({ 256*2, 224, 256, 224 });
	scrollSrc.push_back({ 256*3, 224, 256, 224 });


	scrollSrc.push_back({ 0, 224*2, 256, 224 });
	scrollSrc.push_back({ 256, 224*2, 256, 224 });
	scrollSrc.push_back({ 256*2, 224*2, 256, 224 });
	scrollSrc.push_back({ 256*3, 224*2, 256, 224 });

	scrollCounter = 0.0f;
	scrollPauseTrigger = 500;
	scrollPauseCounter = scrollPauseTrigger;
	pauseDone = false;


	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	music = Mix_LoadMUS("audio/titleTheme.wav");
	if (music == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	Mix_VolumeMusic(10);
	Mix_PlayMusic(music, -1);

}

TitleScene::~TitleScene()
{
	Mix_FreeMusic(music);
	music = NULL;
	Mix_Quit();

}

void TitleScene::update(float elapsed)
{
	if (phase == 0)
	{
		// Move to next frame
		if (fadeCounter <= 0)
		{
			fadeIndex = (fadeIndex + 1) % 4;
			fadeCounter = fadeTrigger;
		}
		else
			fadeCounter -= elapsed;


		// Move to next frame
		if (splashCounter <= 0)
		{
			splashIndex = (splashIndex + 1) % 2;
			splashCounter = splashTrigger;
		}
		else
			splashCounter -= elapsed;


		// Falling
		if (fallCounter <= 0)
		{
			for (int i = 0; i < fallDst.size(); i++)
			{
				fallDst.at(i).y++;
				if (fallDst.at(i).y > 900)
					fallDst.at(i).y = 700;
			}

			fallCounter = fallTrigger;
		}
		else
			fallCounter -= elapsed;



		// Move to phase 1
		if (phaseCounter <= 0)
		{
			texAlpha -= (elapsed / 5.0f);

			if (texAlpha > 0)
				SDL_SetTextureAlphaMod(tex, texAlpha);
			else if (texAlpha <= 0.0f)
			{
				phase = 1;
				texAlpha = 255.0f;
				SDL_SetTextureAlphaMod(tex, texAlpha);
				resetScroll();
				pauseDone = false;
				scrollPauseCounter = scrollPauseTrigger;
			}

		}
		else
			phaseCounter -= elapsed;


	}

	else if (phase == 1)
	{

		if (scrollDst.at(scrollDst.size() - 1).y <= 600)
		{
			texAlpha -= (elapsed / 10.0f);
			if (texAlpha > 0)
				SDL_SetTextureAlphaMod(tex, texAlpha);
			else if (texAlpha <= 0.0f)
			{
				phase = 0;
				texAlpha = 255.0f;
				SDL_SetTextureAlphaMod(tex, texAlpha);

				phaseCounter = phaseTrigger;
			}
		}

		else
		{
			scrollCounter += elapsed;
			if (scrollCounter > 5.0f)
			{
				// Pause here at least
				if (scrollDst.at(0).y <= 0)
				{
					if (!pauseDone)
					{
						if (scrollPauseCounter <= 0)
							pauseDone = true;
						else
							scrollPauseCounter -= elapsed;
					}
					else
					{
						for (int i = 0; i < scrollDst.size(); i++)
						{
							scrollDst.at(i).y--;
						}
					}
				}
				else
				{
					for (int i = 0; i < scrollDst.size(); i++)
					{
						scrollDst.at(i).y--;
					}
				}

				scrollCounter = 0.0f;
			}
		}
	}
}

void TitleScene::draw(Graphics& graphics)
{

	if (phase == 0)
	{

		SDL_Rect titleSrc = { titleBase.x + 256 * fadeIndex, titleBase.y, titleBase.w, titleBase.h };
		graphics.drawTexture(tex, &titleSrc, NULL);

		SDL_Rect splashSrc = { splashBase.x + 32 * splashIndex, splashBase.y, splashBase.w, splashBase.h };
		graphics.drawTexture(tex, &splashSrc, &splashDest);

		SDL_Rect fallSrc = { 0, fallBase.y, fallBase.w, fallBase.h };
		for (int i = 0; i < fallDst.size(); i++)
		{
			if (fallDst.at(i).y < 720)
			{
				fallSrc.x = fallBase.x;
			}
			else if (fallDst.at(i).y < 750)
			{
				fallSrc.x = fallBase.x + 32;
			}
			else
			{
				fallSrc.x = fallBase.x + 64;
			}

			graphics.drawTexture(tex, &fallSrc, &fallDst.at(i));
		}
	}
	else if (phase == 1)
	{
		for (int i = 0; i < scrollSrc.size(); i++)
		{
			graphics.drawTexture(tex, &scrollSrc.at(i), &scrollDst.at(i));
		}
	}
}

void TitleScene::handleInput(SDL_Event& event)
{
	// Press Enter to exit the Title Screen
	if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
	{
		Mix_HaltMusic();
		sceneDone = true;
	}
}

bool TitleScene::sceneSwitch()
{
	return sceneDone;
}

std::string TitleScene::nextScene()
{
	return nextSc;
}

void TitleScene::resetScroll()
{
	scrollDst.clear();
	scrollDst.push_back({ 0, 896, 1024, 896 });
	scrollDst.push_back({ 0, 896*2, 1024, 896 });
	scrollDst.push_back({ 0, 896*3, 1024, 896 });
	scrollDst.push_back({ 0, 896*4, 1024, 896 });
	scrollDst.push_back({ 0, 896*5, 1024, 896 });
	scrollDst.push_back({ 0, 896*6, 1024, 896 });
	scrollDst.push_back({ 0, 896*7, 1024, 896 });
	scrollDst.push_back({ 0, 896*8, 1024, 896 });
}

bool TitleScene::playerActive()
{
	return false;
}

bool TitleScene::hudActive()
{
	return false;
}