#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureFilePath)
{
	objTexture = TextureManager::LoadTexture(textureFilePath);

	xPos = 0;
	yPos = 0;

	srcRect.w = srcRect.h = 16;
	srcRect.x = srcRect.y = 0;

	destRect.x = xPos;
	destRect.y = yPos;
	destRect.x = destRect.y = 64;
}

GameObject::GameObject(const char* textureFilePath, SDL_Rect srcRect, SDL_Rect destRect)
{
	objTexture = TextureManager::LoadTexture(textureFilePath);

	this->srcRect = srcRect;
	this->destRect = destRect;
}

void GameObject::Update()
{
	
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}