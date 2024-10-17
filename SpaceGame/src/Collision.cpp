#include "Collision.h"
#include "ECS/ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if (rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y)
	{
		//std::cout << " Hit : " << std::endl;
		return true;
	}

	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	/*if (colA.tag != colB.tag)
	{
		if (AABB(colA.collider, colB.collider))
		{
			std::cout << colA.tag << "Hit : " << colB.tag << std::endl;
			return true;
		}
		else
			return false;
	}
	else
		return false;*/

	if (AABB(colA.collider, colB.collider))
	{
		//std::cout << colA.tag << " Hit : " << colB.tag << std::endl;
		return true;
	}
	else
		return false;
}