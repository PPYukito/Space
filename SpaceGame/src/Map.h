#pragma once
#include "Game.h"

class Map
{

public:
	Map(int srcX, int srcY);
	~Map();

	void LoadMap();
	void DrawMap();

	void Update();

	Vector2D position;

	const int& MapWidth() { return destRect.w; }
	const int& MapHeight() { return destRect.h; }

private:
	SDL_Rect srcRect, destRect;
	SDL_Texture* mapTexture;
	float scale = 4.0f;

};