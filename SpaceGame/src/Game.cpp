#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"
#include "Vector2D.h"
#include "AssetManager.h"

Map* map;
Manager manager;
Vector2D previousPlayerPos;
float screenRelatePosX;

bool Game::isRunning = false;
SDL_Renderer* Game::renderer = nullptr;
AssetManager* Game::assets = new AssetManager(&manager);
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, screenWidth, screenHeight };

auto& player(manager.AddEntity());
auto& enemy(manager.AddEntity());
auto& planetEye (manager.AddEntity());
auto& planetMarsh(manager.AddEntity());
auto& planetBall(manager.AddEntity());
auto& leftCollider(manager.AddEntity());
auto& bottomCollider(manager.AddEntity());
auto& rightCollider(manager.AddEntity());
auto& topCollider(manager.AddEntity());

auto& players(manager.GetGroup(Game::groupPlayers));
auto& enemies(manager.GetGroup(Game::groupEnemies));
auto& planets(manager.GetGroup(Game::groupPlenets));
auto& colliders(manager.GetGroup(Game::groupColliders));

Game::Game()
{
	std::cout << "Game Start!!" << std::endl;
}

Game::~Game()
{}

void Game::Init(const char* title, int xPos, int yPos, bool fullScreen)
{
	int flags = 0;
	if (fullScreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Game has been initialized!!" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, screenWidth, screenHeight, flags);
		if (window)
		{
			std::cout << "Window has been created!!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer has been created!!" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	
	assets->AddTexture(GetShip(Game::blue), "assets/ships/Blue.png");
	assets->AddTexture(GetShip(Game::brown), "assets/ships/brown.png");
	assets->AddTexture(GetShip(Game::gray), "assets/ships/Gray2.png");

	assets->AddTexture("edge", "assets/maps/edge.png");

	assets->AddTexture("planetEye", "assets/planets/eyePlanet.png");
	assets->AddTexture("planetMarsh", "assets/planets/marshmellow.png");
	assets->AddTexture("planetBall", "assets/planets/pokeballPlanet.png");

	assets->AddTexture("enemy", "assets/enemies/green.png");
	//assets->AddTexture("bullet", "assets/projectiles/projectiles.png");

	previousPlayerPos.x = (screenWidth / 2) - 32;
	previousPlayerPos.y = screenHeight / 2;

	player.AddComponent<TransformComponent>(previousPlayerPos.x, previousPlayerPos.y);
	player.AddComponent<SpriteComponent>(GetShip(Game::blue));
	player.AddComponent<KeyboardController>();
	//player.GetComponent<KeyboardController>().Init(); // we don't have to init, because ECS already do that when we add component to player;
	player.AddComponent<ColliderComponent>("player");
	player.AddGroup(groupPlayers);

	enemy.AddComponent<TransformComponent>(0.0f, 0.0f, 128, 126, 1.0f);
	enemy.AddComponent<SpriteComponent>("enemy");
	enemy.AddComponent<ColliderComponent>("enemy");
	enemy.AddGroup(groupEnemies);
	enemy.AddGroup(groupColliders);

	planetEye.AddComponent<TransformComponent>(-300, -300, 128, 128, 1.0f);
	planetEye.AddComponent<SpriteComponent>("planetEye");
	planetEye.AddComponent<ColliderComponent>("planet");
	planetEye.AddGroup(groupPlenets);
	planetEye.AddGroup(groupColliders);

	planetMarsh.AddComponent<TransformComponent>(-600, -800, 128, 128, 1.0f);
	planetMarsh.AddComponent<SpriteComponent>("planetMarsh");
	planetMarsh.AddComponent<ColliderComponent>("planet");
	planetMarsh.AddGroup(groupPlenets);
	planetMarsh.AddGroup(groupColliders);

	planetBall.AddComponent<TransformComponent>(700, -1000, 128, 128, 1.0f);
	planetBall.AddComponent<SpriteComponent>("planetBall");
	planetBall.AddComponent<ColliderComponent>("planet");
	planetBall.AddGroup(groupPlenets);
	planetBall.AddGroup(groupColliders);

	//CreateProjectile(Vector2D(100, 100), 200, 2, "bullet");
	map = new Map(0, 0);

	screenRelatePosX = (map->MapWidth() - Game::screenWidth) / 2;

	//edge colliders
	bottomCollider.AddComponent<TransformComponent>(-screenRelatePosX, 590, map->MapWidth(), 10, 1);
	bottomCollider.AddComponent<ColliderComponent>("edgeCollider");
	bottomCollider.AddGroup(groupColliders);

	leftCollider.AddComponent<TransformComponent>(-screenRelatePosX - 5, -(map->MapHeight() - screenHeight) - 10, 10, map->MapHeight(), 1);
	leftCollider.AddComponent<ColliderComponent>("edgeCollider");
	leftCollider.AddGroup(groupColliders);

	topCollider.AddComponent<TransformComponent>(-screenRelatePosX, -(map->MapHeight() - screenHeight) - 10, map->MapWidth(), 10, 1);
	topCollider.AddComponent<ColliderComponent>("edgeCollider");
	topCollider.AddGroup(groupColliders);

	rightCollider.AddComponent<TransformComponent>(1990, -(map->MapHeight() - screenHeight), 10, map->MapHeight(), 1);
	rightCollider.AddComponent<ColliderComponent>("edgeCollider");
	rightCollider.AddGroup(groupColliders);
	//--------------
}


void Game::HandleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::Update()
{
	SDL_Rect playerCollider = player.GetComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.GetComponent<TransformComponent>().position;

	manager.Refresh();
	manager.Update();

	for (auto& cc : colliders)
	{
		SDL_Rect cCol = cc->GetComponent<ColliderComponent>().collider;

		if (Collision::AABB(cCol, playerCollider))
		{
			player.GetComponent<TransformComponent>().position = playerPos;
		}
	}

	if (playerPos.x != previousPlayerPos.x || playerPos.y != previousPlayerPos.y)
	{
		camera.x = (playerPos.x + (playerCollider.w / 2)) - (screenWidth / 2);
		camera.y = playerPos.y - (screenHeight / 2);

		previousPlayerPos = playerPos;

		if (camera.x < map->position.x - 10)
			camera.x = map->position.x - 10;

		if (camera.y < map->position.y - 10)
			camera.y = map->position.y - 10;

		if (camera.x > screenRelatePosX + 10)
			camera.x = screenRelatePosX + 10;

		if (camera.y > 0 + 10)
			camera.y = 0 + 10;

		map->Update();
	}

}

void Game::Render()
{
	SDL_RenderClear(renderer);

	map->DrawMap(); // have to do something with this;
	//manager.Draw();

	for (auto& p : players)
	{
		p->Draw();
	}

	for (auto& e : enemies)
	{
		e->Draw();
	}

	for (auto& pl : planets)
	{
		pl->Draw();
	}

	/*for (auto& cc : colliders)
	{
		cc->Draw();
	}*/

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game has been cleaned!!" << std::endl;
}

std::string Game::GetShip(Game::ShipType shipType)
{
	std::string ship = "";
	switch (shipType)
	{
	case Game::blue:
		ship = "shipBlue";
		break;
	case Game::brown:
		ship = "shipBrown";
		break;
	case Game::gray:
		ship = "shipGray";
		break;
	default:
		ship = "shipBlue";
		break;
	}

	return ship;
}