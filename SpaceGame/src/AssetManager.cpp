#include "AssetManager.h"
#include "ECS/Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

void AssetManager::AddTexture(std::string texID, const char* path)
{
	textures.emplace(texID, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string texID)
{
	return textures[texID];
}