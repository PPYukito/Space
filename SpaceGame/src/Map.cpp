#include "Map.h"
#include "TextureManager.h"

Map::Map(int srcX, int srcY)
{
	mapTexture = TextureManager::LoadTexture("assets/maps/map1.png");
	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = 800;
	srcRect.h = 1200;

	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;
	position.x = destRect.x = -((destRect.w - Game::screenWidth) / 2);
	position.y = destRect.y = -(destRect.h - Game::screenHeight);
}

Map::~Map()
{
	SDL_DestroyTexture(mapTexture);
}

void Map::LoadMap()
{

}

void Map::Update()
{
	destRect.x = position.x - Game::camera.x;
	destRect.y = position.y - Game::camera.y;
}

void Map::DrawMap()
{
	TextureManager::Draw(mapTexture, srcRect, destRect);
}