
#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include<typeinfo>
#include "Destination.h"

SpriteComponent::SpriteComponent(Actor* owners, int drawOrder)
	:Component(owners)
	, texture(-1)
	, drawOrder(drawOrder)
	, texWidth(0)
	, texHeight(0)
{
	owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw()
{

	if (texture != -1)// handle
	{
		//SDL_Rect r;
		int x, y;
		float s, th;
		float r;// 衝突円の半径
		x = owner->GetPosition().x;
		y = owner->GetPosition().y;
		s = owner->GetScale();
		th = owner->GetRotation();

		r = owner->GetcRaius();		// 衝突円の半径を返すメソッドを呼ぶ
		r *= s;
		// ステートがActiveのオブジェクトのみ表示
		if (owner->GetState() == Actor::EActive)
		{
			DrawCircleAA(x, y, r, 100, GetColor(255, 255, 255), 0);
			DrawRotaGraph(x, y, s, th, texture, TRUE);
		}
		
		// ゴール当たり判定表示
		if (typeid(*owner) == typeid(class Destination))
		{
			Destination* pGoal = (Destination*)owner;
			Vector2 size;
			size = owner->GetBsize();
			float x1, x2, y1, y2;
			// 衝突矩形の左上の座標と右下の座標を計算
			x1 = x + s * size.x / 2.0f;
			x2 = x - s * size.x / 2.0f;
			y1 = y + s * size.y / 2.0f;
			y2 = y - s * size.y / 2.0f;
			if (pGoal->GetGoalNumber() == YELLOW_BALL_GOAL)
				DrawBox(x1, y1, x2, y2, GetColor(255, 255, 0), 1);
			else
				DrawBox(x1, y1, x2, y2, GetColor(0, 0, 255), 1);
			pGoal = nullptr;
		}
		
	}
}


void SpriteComponent::SetTexture(int textures)
{
	texture = textures;//handle

	GetGraphSize(texture, &texWidth, &texHeight);

}
