#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponent = 32;
constexpr std::size_t maxGroup = 32;

using ComponentBitSet = std::bitset<maxComponent>;
using GroupBitSet = std::bitset<maxGroup>;
using ComponentArray = std::array<Component*, maxComponent>;

class Component
{

public:
	Entity* entity;

	virtual ~Component() {}

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

};

class Entity
{

private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:
	Entity(Manager& mManager) : manager(mManager) {}

	void Update()
	{
		for (auto& c : components)
		{
			c->Update();
		}
	}

	void Draw()
	{
		for (auto& c : components)
		{
			c->Draw();
		}
	}

	bool isActive() const { return active; }
	void Destroy() { active = false; }

	bool HasGroup(Group mGroup)
	{
		return groupBitSet[mGroup];
	}

	void AddGroup(Group mGroup);
	void DelGroup(Group mGroup)
	{
		groupBitSet[mGroup] = false;
	}

	template <typename T> bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr { c };
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template <typename T> T& GetComponent() const
	{
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class Manager
{

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroup> groupedEntities;

public:
	void Update()
	{
		for (auto& e : entities)
		{
			e->Update();
		}
	}

	void Draw()
	{
		for (auto& e : entities)
		{
			e->Draw();
		}
	}

	void Refresh()
	{
		for (auto i(0u); i < maxGroup; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(std::remove_if(begin(v), std::end(v), [i](Entity* mEntity)
				{
					return !mEntity->isActive() || !mEntity->HasGroup(i);
				}
			), std::end(v));

		}

		entities.erase(std::remove_if(
			std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities)
		);
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& GetGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr { e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

};