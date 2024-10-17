#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "../AssetManager.h"

class SpriteComponent : public Component
{

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;

	SpriteComponent(std::string texID)
	{
		/*if (transform == nullptr)
			transform = &entity->GetComponent<TransformComponent>();*/

		SetTexture(texID);
		srcRect.x = srcRect.y = 0;
	}

	/*SpriteComponent(std::string texID, int srcX, int srcY, int desW, int desH)
	{
		SetTexture(texID);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

		destRect.w = desW;
		destRect.h = desH;
	}*/

	SpriteComponent(std::string texID, int srcX, int srcY, int srcW, int srcH)
	{
		SetTexture(texID);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcW;
		srcRect.h = srcH;

		/*destRect.w = desW;
		destRect.h = desH;*/
	}

	~SpriteComponent()
	{
		// SDL_DestroyTexture(texture);
	}

	void Init() override
	{
		if (transform == nullptr)
			transform = &entity->GetComponent<TransformComponent>();

		//srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	/*void Init(int srcX, int srcY, int desW, int desH)
	{
		if (transform == nullptr)
			transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

		destRect.w = desW;
		destRect.h = desH;
	}*/

	void Update() override
	{
		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

	void SetTexture(std::string texID)
	{
		texture = Game::assets->GetTexture(texID);
	}

};