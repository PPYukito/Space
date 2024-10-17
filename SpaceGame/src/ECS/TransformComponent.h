#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{

public:

	Vector2D position;
	Vector2D velocity;

	int height = 64;
	int width = 64;
	float scale = 1;

	int speed = 5;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int w, int h, float sc)
	{
		position.x = x;
		position.y = y;

		width = w;
		height = h;
		scale = sc;
	}

	void Init() override
	{
		velocity.Zero();
	}

	void Update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};