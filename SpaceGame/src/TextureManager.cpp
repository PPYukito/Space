#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filePath)
{
	SDL_Surface* tempSurface = IMG_Load(filePath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}
