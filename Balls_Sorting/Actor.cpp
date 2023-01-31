
#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:state(EActive)
	, position(Vector2::Zero)
	, scale(1.0f)
	, rotation(0.0f)
	, game(game)
{
	game->AddActor(this);
}

Actor::~Actor()
{
	game->RemoveActor(this);

	while (!components.empty())
	{
		delete components.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (state == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : components)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = components.begin();
	for (;
		iter != components.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	components.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(components.begin(), components.end(), component);
	if (iter != components.end())
	{
		components.erase(iter);
	}
}
