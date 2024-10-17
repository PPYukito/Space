#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"

class AssetManager
{

public:
	AssetManager(Manager* man);

	~AssetManager();

	void AddTexture(std::string texID, const char* path);
	SDL_Texture* GetTexture(std::string texID);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;

};