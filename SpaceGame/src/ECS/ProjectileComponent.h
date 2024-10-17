#pragma once
#include "ECS.h"
#include "Components.h"

class ProjectileComponent : public Component
{

private:
	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;

public:
	ProjectileComponent(int rng, int sp) : range(rng), speed(sp)
	{}

	~ProjectileComponent()
	{}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
	}

	void Update() override
	{
		distance += speed;

		if (distance > range)
		{
			entity->Destroy();
		}
		else if (transform->position.x > Game::screenWidth || 
				transform->position.x < 0 ||
				transform->position.y > Game::screenHeight ||
				transform->position.y < 0)
		{
			entity->Destroy();
		}
	}

};