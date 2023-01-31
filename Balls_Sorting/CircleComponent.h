#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent :public Component
{
public:
	CircleComponent(class Actor* owner);

	// �Փˉ~�̔��a��ݒ�
	void SetRadius(float radi) { radius = radi; };
	// �Փˉ~�̔��a�̒l��Ԃ�
	float GetRadius() const;

	// �Փˉ~�̒��S�̍��W��Ԃ�
	const Vector2 GetCenter() const;

private:
	// �Փˉ~�̔��a
	float radius;
};

// �Փˉ������̌�������
bool Intersect(const CircleComponent& a, const CircleComponent& b);