#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include <vector>

class AssetManager;
class ColliderComponent;

class Game
{

public:
	Game();

	~Game();

	void Init(const char* title, int xPos, int yPos, bool fullScreen);

	void HandleEvents();

	void Update();

	void Render();

	void Clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	// static std::vector<ColliderComponent*> colliders;

	static const int screenWidth = 800;
	static const int screenHeight = 600;
	static AssetManager* assets;
	static bool isRunning;
	static SDL_Rect camera;

	enum GroupLabels : std::size_t
	{
		groupPlayers,
		groupEnemies,
		groupPlenets,
		groupColliders
	};

	enum ShipType : std::size_t
	{
		blue,
		brown,
		gray
	};

	static std::string GetShip(Game::ShipType shipType);

private:
	SDL_Window* window;

};

