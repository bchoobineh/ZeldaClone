#include "fileselect.h"
#include <algorithm>

FileSelect::FileSelect(std::string path, Graphics& graphics)
{
	// Setup the File Select Texture
	tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path));

	// Start at screen 0
	screenNum = 0;

	// Profile Index
	for (int i = 0; i < 3; i++)
	{
		playerProfile tmp;
		tmp.lifeCount = 3;
		tmp.rubyCount = 0;
		profiles.push_back(tmp);
	}
	profileIndex = 0;
	 
	sceneDone = false;

	// File Select Screen 1
	selectSrc = { 1, 1, 256, 224 };

	// File Register Screen
	registerSrc = { 258, 1, 256, 224 };

	// Screen 1 Name Base
	sc1NameBase = { 72*4, 80*4, 32, 32 };
	rubyBase = { (72+8) * 4, 88 * 4, 32, 32 };
	numBase = { 303, 172, 16, 16 };
	lifeBase = { 577, 320, 32, 32 };

	// Screen 2 Flash Base
	flashSrc = { 94, 240, 8, 8 };
	flashBase = { 190, 128*4, 32, 32 };
	flashCurrent = flashBase;
	flashTrigger = true;
	flashCounter = 250.0f;
	nameFlashLoc = Vector2(0, 0);

	nameFlashBase = { 448, 160, 32, 32 };
	nameFlashCurrent = nameFlashBase;

	// Link Src
	linkSrc = { 1, 230, 16, 16 };
	linkDstBase = { 48 * 4, 81 * 4, 16 * 4, 16 * 4 };


	heartSrc = { 52, 230, 8, 8 };
	heartIndex = 0;

		
	heartLoc.push_back({ 40*4, 85*4, 8*4, 8*4 });
	heartLoc.push_back({ 40*4, 109*4, 8 * 4, 8 * 4 });
	heartLoc.push_back({ 40*4, 133 * 4, 8 * 4, 8 * 4 });
	heartLoc.push_back({ 40 * 4, 161 * 4, 8 * 4, 8 * 4 });
	heartLoc.push_back({ 40 * 4, 177 * 4, 8 * 4, 8 * 4 });

	heartLoc2.push_back({ 270, 40 * 4 ,  32, 32});
	heartLoc2.push_back({ 270, 64 * 4, 32, 32});
	heartLoc2.push_back({ 270, 88 * 4, 32, 32});
	heartLoc2.push_back({ 270, 112 * 4, 32, 32});


}

FileSelect::~FileSelect()
{}

void FileSelect::update(float elapsed)
{
	if (flashCounter <= 0)
	{
		flashTrigger = !flashTrigger;
		flashCounter = 250.0f;
	}
	else
		flashCounter -= elapsed;

}

void FileSelect::draw(Graphics& graphics)
{
	if (screenNum == 0)
		drawScreen1(graphics);
	else if (screenNum == 1)
		drawScreen2(graphics);

}

void FileSelect::handleInput(SDL_Event& event)
{
	if (screenNum == 0)
	{
		if (event.key.repeat == 0)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				heartIndex = std::max(heartIndex - 1, 0);
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				heartIndex = std::min(heartIndex + 1, 4);
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				// Go to the file register screen
				if (heartIndex == 3)
				{
					screenNum = 1;
					linkDstBase.x += 128;
					linkDstBase.y -= 160;
					heartIndex = 0;
				}
				else
				{
					if (profiles.at(heartIndex).name.size() > 0)
					{
						sceneDone = true;
					}
				}
			}
		}
	}

	else if (screenNum == 1)
	{
		if (event.key.repeat == 0)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				nameFlashLoc.y--;
				flashCurrent.y -= 64;
				if (flashCurrent.y < 512)
				{
					flashCurrent.y = 512;
					nameFlashLoc.y++;
				}
			}

			else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				nameFlashLoc.y++;
				flashCurrent.y += 64;
				if (flashCurrent.y > 704)
				{
					flashCurrent.y = 704;
					nameFlashLoc.y--;
				}
	
			}

			else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				nameFlashLoc.x++;
				flashCurrent.x += 64;
				if (flashCurrent.x > 830)
				{
					nameFlashLoc.x--;
					flashCurrent.x = 830;
				}
			}

			else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				nameFlashLoc.x--;
				flashCurrent.x -= 64;
				if (flashCurrent.x < 190)
				{
					nameFlashLoc.x++;
					flashCurrent.x = 190;
				}
			}

			else if(event.key.keysym.scancode == SDL_SCANCODE_Z)
			{
				addLetter();
			}

			else if (event.key.keysym.scancode == SDL_SCANCODE_RSHIFT)
			{
				heartIndex = std::min(heartIndex + 1, 3);
			}

			else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				// Go back to screen 1
				heartIndex = 0;
				screenNum = 0;
				linkDstBase.x -= 128;
				linkDstBase.y += 160;
			}
		}
	}

}

bool FileSelect::sceneSwitch()
{
	return sceneDone;
}

std::string FileSelect::nextScene()
{
	return "Overworld";
}

bool FileSelect::playerActive()
{
	return false;
}

void FileSelect::drawScreen1(Graphics& graphics)
{
	// Draw backdrop
	graphics.drawTexture(tex, &selectSrc, NULL);

	// Draw the Link icons
	SDL_Rect tmp = linkDstBase;
	for (int i = 0; i < 3; i++)
	{
		graphics.drawTexture(tex, &linkSrc, &tmp);
		tmp.y += 96;
	}

	// Draw existing profiles
	for (int i = 0; i < profiles.size(); i++)
	{
		if (profiles.at(i).name.size() > 0)
		{
			drawName(profiles.at(i).name, sc1NameBase, graphics);
			graphics.drawTexture(tex, &numBase, &rubyBase);

			for (int j = 0; j < profiles.at(i).lifeCount; j++)
			{
				SDL_Rect tmp = lifeBase;
				tmp.x = lifeBase.x + (32*j);
				graphics.drawTexture(tex, &heartSrc, &tmp);
			}

		}
	}

	// Draw Heart Select Cursor
	graphics.drawTexture(tex, &heartSrc, &heartLoc.at(heartIndex));
}

void FileSelect::drawScreen2(Graphics& graphics)
{
	if (flashTrigger)
	{
		graphics.drawTexture(tex, &flashSrc, &flashCurrent);
		graphics.drawTexture(tex, &flashSrc, &nameFlashCurrent);
	}

	drawName(profiles.at(profileIndex).name, nameFlashBase, graphics);


	graphics.drawTexture(tex, &registerSrc, NULL);

	// Draw the Link icons
	SDL_Rect tmp = linkDstBase;
	for (int i = 0; i < 3; i++)
	{
		graphics.drawTexture(tex, &linkSrc, &tmp);
		tmp.y += 96;
	}

	// Draw Heart Select Cursor
	graphics.drawTexture(tex, &heartSrc, &heartLoc2.at(heartIndex));
}

void FileSelect::addLetter()
{
	// Add Character
	profiles.at(profileIndex).name.push_back(nameFlashLoc);

	// Update Flash
	nameFlashCurrent.x += 32;
}

void FileSelect::drawName(std::vector<Vector2> name, SDL_Rect base, Graphics &graphics)
{
	//printf("Name Size: %d\n", name.size());

	for (int i = 0; i < name.size(); i++)
	{
		SDL_Rect src = { 303 + 16 * name.at(i).x, 126 + 16 * name.at(i).y, 16, 16 };
		SDL_Rect dst = { base.x + 32 * i, base.y, 32, 32 };
		graphics.drawTexture(tex, &src, &dst);
	}

}

bool FileSelect::hudActive()
{
	return false;
}