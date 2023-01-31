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

// �~�̔��a�ɃX�P�[���l�������Ď��ۂ̑傫����Ԃ�
float CircleComponent::GetRadius()const
{
	return owner->GetScale() * radius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// �~�̒��S�������v�Z
	Vector2 diff = a.GetCenter() - b.GetCenter();
	// �x�N�g���������ɕϊ�
	float distSq = diff.LengthSq();

	// �Փˉ~�̘a���v�Z
	// ���a���v�Z
	float radiiSq = a.GetRadius() + b.GetRadius();	
	// ���a���v�Z
	radiiSq *= radiiSq;								

	return distSq <= radiiSq;

}

