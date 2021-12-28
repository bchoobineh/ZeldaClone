#include "scene.h"
#include "tinyxml2.h"
#include <cmath>
#include <algorithm>

using namespace tinyxml2;

Scene::Scene()
{}

Scene::Scene(std::string path, Graphics &graphics)
{
	// Load the Game Map
	loadMap(path, graphics);
}

Scene::~Scene()
{}

void Scene::loadMap(std::string path, Graphics& graphics)
{
	XMLDocument doc;
	
	if (doc.LoadFile(path.c_str()) != XML_SUCCESS)
	{
		printf("Map Loading Failed\n");
		exit(1);
	}

	printf("Loading Map\n");

	// Get Dimensions of Map
	XMLElement* mapNode = doc.FirstChildElement("map");
	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	sceneSize = Vector2(width, height);

	// Get Tile Size
	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	tileSize = Vector2(tileWidth, tileHeight);

	// Parse Tilesets
	XMLElement* tilesetNode = mapNode->FirstChildElement("tileset");
	while (tilesetNode)
	{
		// Find first GID
		int fGID;
		tilesetNode->QueryIntAttribute("firstgid", &fGID);

		// Get Tileset Texture
		const char* tileSource = tilesetNode->FirstChildElement("image")->Attribute("source");
		std::string src(&tileSource[3]);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(src));

		// Create and push back tileset

		tilesets.push_back(Tileset(tex, fGID));

		tilesetNode = tilesetNode->NextSiblingElement("tileset");


	}

	// Parse Layers
	XMLElement* layerNode = mapNode->FirstChildElement("layer");
	while (layerNode)
	{
		XMLElement* dataNode = layerNode->FirstChildElement("data");
		while (dataNode)
		{
			XMLElement* tileNode = dataNode->FirstChildElement("tile");
			int tileCounter = 0;
			while (tileNode)
			{
				// No Tile here
				if (tileNode->IntAttribute("gid") == 0)
				{
					tileCounter++;

					// There is another tile
					if (tileNode->NextSiblingElement("tile"))
					{
						tileNode = tileNode->NextSiblingElement("tile");
						continue;
					}
					else
						break;
				}

				// Find the Tileset associated with the GID
				int GID = tileNode->IntAttribute("gid");
				Tileset st;
				int near = 0;
				for (int i = 0; i < tilesets.size(); i++)
				{
					if (tilesets.at(i).fGID <= GID)
					{
						if (tilesets.at(i).fGID > near)
						{
							near = tilesets.at(i).fGID;
							st = tilesets.at(i);
						}
					}
				}

				// If we somehow didn't find Tileset
				if (st.fGID < 0)
				{

					printf("Didnt Find Tileset\n");
					tileCounter++;
					if (tileNode->NextSiblingElement("tile"))
					{
						tileNode = tileNode->NextSiblingElement("tile");
						continue;
					}
					else
						break;
				}

				// Find tile's position in the world
				int xPos = (tileCounter % width) * tileWidth;
				int yPos = tileHeight * (tileCounter / width);
				Vector2 screenPos = Vector2(xPos, yPos);

				// Find the position of the tile in the sprite sheet
				int sheetWidth, sheetHeight;
				SDL_QueryTexture(st.tex, NULL, NULL, &sheetWidth, &sheetHeight);
				int sheetX = (GID % (sheetWidth / tileWidth) - 1) * tileWidth;
				int sheetY = tileHeight * ((GID - st.fGID) / (sheetWidth / tileWidth));
				Vector2 sheetPosition = Vector2(sheetX, sheetY);

				// Build Tile
				Tile tile(st.tex, Vector2(tileWidth, tileHeight), sheetPosition, screenPos);
				tiles.push_back(tile);



				tileCounter++;
				tileNode = tileNode->NextSiblingElement("tile");
			}

			dataNode = dataNode->NextSiblingElement("data");
		}

		layerNode = layerNode->NextSiblingElement("layer");
	}


	// Parse Object Groups
	XMLElement* objectNode = mapNode->FirstChildElement("objectgroup");
	while (objectNode)
	{
		const char* name = objectNode->Attribute("name");
		std::string sName(name);
		
		// Check Collisions
		if (sName == "Collisions")
		{
			XMLElement* objNode = objectNode->FirstChildElement("object");
			while (objNode)
			{
				float x, y, width, height;
				x = objNode->FloatAttribute("x");
				y = objNode->FloatAttribute("y");
				width = objNode->FloatAttribute("width");
				height = objNode->FloatAttribute("height");

				collisions.push_back(Rectangle(std::ceil(x) * 4, std::ceil(y+56) * 4, std::ceil(width) * 4, std::ceil(height) * 4));

				objNode = objNode->NextSiblingElement("object");
			}
		
		}



		objectNode = objectNode->NextSiblingElement("objectgroup");
	}

	for (int i = 0; i < collisions.size(); i++)
	{
		printf("X: %d Y: %d Width: %d Height: %d\n", collisions.at(i).getLeft(), collisions.at(i).getBot(), collisions.at(i).getWidth(), collisions.at(i).getHeight());
	}
}

std::vector<Rectangle> Scene::checkRectCollisions(const Rectangle& rect)
{
	std::vector<Rectangle> colliders;
	for (int i = 0; i < collisions.size(); i++)
	{
		if (collisions.at(i).inCollision(rect))
		{
			colliders.push_back(collisions.at(i));
		}
	}
	return colliders;
}