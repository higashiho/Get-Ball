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

// 円の半径にスケール値をかけて実際の大きさを返す
float CircleComponent::GetRadius()const
{
	return owner->GetScale() * radius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// 円の中心距離を計算
	Vector2 diff = a.GetCenter() - b.GetCenter();
	// ベクトルを距離に変換
	float distSq = diff.LengthSq();

	// 衝突円の和を計算
	// 半径を計算
	float radiiSq = a.GetRadius() + b.GetRadius();	
	// 直径を計算
	radiiSq *= radiiSq;								

	return distSq <= radiiSq;

}

