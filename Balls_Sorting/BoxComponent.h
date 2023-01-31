#include "Actor.h"
#pragma once
#include "Component.h"
#include "Math.h"
#include "CircleComponent.h"
#include"BoxComponent.h"

class BoxComponent : public Component// Componentの継承クラス宣言
{
public:
	BoxComponent(class Actor* owner);						// クラスのコンストラクター
	void  SetPoint(Vector2 max1, Vector2 min1) { max = max1; min = min1; }
	// 衝突矩形の左上座標と右下座標を設定するメソッドの実装
	Vector2  GetmaxPoint() { return max; }					// 衝突矩形の右下座標を返すメソッド実装
	Vector2  GetminPoint() { return min; }					// 衝突矩形の左上座標を返すメソッド実装

	const Vector2 GetCenter() const;						// 衝突矩形の中心の座標を返すメソッド

	Vector2 dd;												// 衝突矩形の考査領域のｘ、ｙ方向成分
private:
	Vector2 max, min;// 衝突矩形の右下座標、左上座標
};

// 衝突円と衝突矩形の交差判定関数
bool Intersect(const CircleComponent& a, BoxComponent& b);

// 衝突矩形どうしの交差判定関数
bool Intersect(BoxComponent& a, BoxComponent& b);

