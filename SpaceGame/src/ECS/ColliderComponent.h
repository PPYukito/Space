#pragma once
#include <string>
#include "SDL.h"
#include "ECS.h"
#include "Components.h"

class ColliderComponent : public Component
{

public:
	SDL_Rect collider;
	std::string tag;

	SDL_Rect srcRect, destRect;

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	/*ColliderComponent(std::string t, SDL_Rect srcR, SDL_Rect destR)
	{
		tag = t;
		srcRect = srcR;
		destRect = { collider.x, collider.y, collider.w, collider.h };
	}*/

	void Init() override
	{
		if (!entity->HasComponent<TransformComponent>())
			entity->AddComponent<TransformComponent>();

		transform = &entity->GetComponent<TransformComponent>();

		//Game::colliders.push_back(this);
		//entity->AddGroup(Game::groupColliders);
	}

	void Update() override
	{
		if (tag != "terrain")
		{
			
		}

		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);

		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}

};