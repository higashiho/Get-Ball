#include "Destination.h"
#include "BoxComponent.h"

#include "AnimSpriteComponent.h"

Destination::Destination(Game* game, Vector2 pos,int num):Actor(game)
{
	goalNumber = num;
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);	// Animationスプライトを作成してそのポインターを代入
	std::vector<int> anims = {									// Animation の各フレームのハンドルをvector型配列に代入
		game->GetTexture("Image/Goal.png"),
	};
	asc->SetAnimTextures(anims);// AnimationComponent クラスのメソッドで各フレームのハンドルを登録
	asc = nullptr;
	delete asc;
	SetPosition(pos);
	Vector2 max1, min1, size;
	// 実際の矩形サイズ
	size.x = 240.f; size.y = 240.f;

	// 衝突矩形の左上のの座標と右下の座標
	max1.x = pos.x + GetScale() * size.x / 2.0f;
	max1.y = pos.y + GetScale() * size.y / 2.0f;
	min1.x = pos.x - GetScale() * size.x / 2.0f;
	min1.y = pos.y - GetScale() * size.y / 2.0f;

	// 衝突矩形（BoxComponent）の追加
	boxCol = new BoxComponent(this);
	boxCol->SetPoint(max1, min1);
	SetBsize(size);
}

Destination::~Destination()
{
	SAFE_DELETE(boxCol);
}
// 全体挙動
void Destination::UpdateActor(float deltaTime)
{
	Collision(goalNumber);
}

// 当たり判定
void Destination::Collision(int patternBall)
{
	for (auto other : GetGame()->GetSortingBowls())
	{
		if(other == nullptr)
			continue;
		// 当たったボールがドラッグ後離された場合のみ処理
		if (other->GetBallDrop())
		{
			if (Intersect(*(other->GetCircle()), *boxCol) && other->GetState() == EActive)
				// 離されたのが指定のの場合
				if (other->GetThisBallPattern() == patternBall)
				{
					GetGame()->CountUp((UINT)other->GetRadius());
					other->SetState(EPaused);
				}
			// それ以外の場合
				else
					GetGame()->SetGameOverFlag(true);
			break;
		}
	}
}