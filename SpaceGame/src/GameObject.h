#pragma once
#include "Game.h"

class GameObject
{

public:
	GameObject(const char* textureFilePath);
	GameObject(const char* textureFilePath, SDL_Rect srcRect, SDL_Rect destRect);
	~GameObject();

	void Update();
	void Render();

private:
	int xPos;
	int yPos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};