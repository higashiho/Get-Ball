#include"CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(class Actor* owners)
	:Component(owners),radius(0.0f)
{

}

const Vector2 CircleComponent::GetCenter()const
{
	return owner->GetPosition();
}

// ‰~‚Ì”¼Œa‚ÉƒXƒP[ƒ‹’l‚ğ‚©‚¯‚ÄÀÛ‚Ì‘å‚«‚³‚ğ•Ô‚·
float CircleComponent::GetRadius()const
{
	return owner->GetScale() * radius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// ‰~‚Ì’†S‹——£‚ğŒvZ
	Vector2 diff = a.GetCenter() - b.GetCenter();
	// ƒxƒNƒgƒ‹‚ğ‹——£‚É•ÏŠ·
	float distSq = diff.LengthSq();

	// Õ“Ë‰~‚Ì˜a‚ğŒvZ
	// ”¼Œa‚ğŒvZ
	float radiiSq = a.GetRadius() + b.GetRadius();	
	// ’¼Œa‚ğŒvZ
	radiiSq *= radiiSq;								

	return distSq <= radiiSq;

}

