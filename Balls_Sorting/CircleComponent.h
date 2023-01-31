#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent :public Component
{
public:
	CircleComponent(class Actor* owner);

	// Õ“Ë‰~‚Ì”¼Œa‚ğİ’è
	void SetRadius(float radi) { radius = radi; };
	// Õ“Ë‰~‚Ì”¼Œa‚Ì’l‚ğ•Ô‚·
	float GetRadius() const;

	// Õ“Ë‰~‚Ì’†S‚ÌÀ•W‚ğ•Ô‚·
	const Vector2 GetCenter() const;

private:
	// Õ“Ë‰~‚Ì”¼Œa
	float radius;
};

// Õ“Ë‰““¡‚ÌŒğ·”»’è
bool Intersect(const CircleComponent& a, const CircleComponent& b);