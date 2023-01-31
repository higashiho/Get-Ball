#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owners, int updateOrder)
	:owner(owners)
	, updateOrder(updateOrder)
{
	// Add to actor's vector of components
	owner->AddComponent(this);
}

Component::~Component()
{
	owner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}
