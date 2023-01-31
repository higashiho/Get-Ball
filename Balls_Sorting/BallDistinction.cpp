#include "BallDistinction.h"
#include "AnimSpriteComponent.h"
#include"CircleComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Input.h"
#include "DxLib.h"

// コンストラクタ
BallDistinction::BallDistinction(Game* game, int bowlsNumber) :BasicBall(game)
{
	// 以下表示設定=========================================
	ballPattern = bowlsNumber;
	std::vector<int> anims;
	asc = new AnimSpriteComponent(this, 100);
	if (bowlsNumber == pBalls.YELLOW_BALL)
	{
		anims = {			
			game->GetTexture("image/HBall.png"),
			game->GetTexture("image/HBall2.png"),
			game->GetTexture("image/HBall3.png"),
			game->GetTexture("image/HBall4.png"),
		};
	}
	else if(bowlsNumber == pBalls.RED_BALL)
	{
		anims = {			
			game->GetTexture("image/SBall.png"),
			game->GetTexture("image/SBall2.png"),
			game->GetTexture("image/SBall3.png"),
			game->GetTexture("image/SBall4.png"),
		};
	}
	else
	{
		anims = {			
			game->GetTexture("image/MBall.png"),
			game->GetTexture("image/MBall2.png"),
			game->GetTexture("image/MBall3.png"),
			game->GetTexture("image/MBall4.png"),
		};
	}
	// 以上表示設定=========================================
	// AnimationComponent クラスのメソッドで1フレームのハンドルを登録
	asc->SetAnimTextures(anims);		


	// 初期設定関数
	Reset();
	//ゲームシーンに追加
	game->AddSortingBowls(this);						
}

// デストラクタ
BallDistinction::~BallDistinction()
{
	GetGame()->RemoveSortingBowls(this);
	/*
	SAFE_DELETE(pOnDrag);
	SAFE_DELETE(pOnMouse);
	SAFE_DELETE(pBallDrop);*/
}

// 全体挙動
void BallDistinction::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// 当たり判定
	Collision();
	// 移動
	Update(deltaTime);

	// マウスポインター挙動
	// エネミーボールは持てないようにする
#ifdef _DEBUG
	GetGame()->GetInput()->MouseController(GetGame(), this);
#else
	if (this->ballPattern != pBalls.ENEMY_BALL)
		GetGame()->GetInput()->MouseController(GetGame(), this);
#endif
		
}

// 更新処理
void BallDistinction::Update(float deltaTime) 
{
	// 現在の位置を取得
	Vector2 pos = GetPosition();

	// 移動
	pos = Movement(pos, deltaTime);

	//周囲の境界との衝突
	//ウィンドウ範囲内かどうか
	if ((pos.x - radius) < cBall.OUT_LINE)
	{
		//x方向速度を反転
		vx *= -cBall.RETURN_SPEED;
		//座標を右に戻す
		pos.x += radius / cBall.RADIUS_ADJUSMENT;

		// 跳ね返り対象を格納していたポインタを初期化する
		sBalls = nullptr;
	}
	if ((pos.x + radius) > (SIZE_X - cBall.OUT_LINE)) 
	{
		vx *= -cBall.RETURN_SPEED;
		//座標を左に戻す
		pos.x += -radius / cBall.RADIUS_ADJUSMENT;
		// 跳ね返り対象を格納していたポインタを初期化する
		sBalls = nullptr;
	}
	if ((pos.y - radius) < cBall.OUT_LINE) 
	{
		//y方向速度を反転
		vy *= -cBall.RETURN_SPEED;					
		//座標を下に戻す
		pos.y += radius / cBall.RADIUS_ADJUSMENT;
		// 跳ね返り対象を格納していたポインタを初期化する
		sBalls = nullptr;
	}
	if ((pos.y + radius) > (SIZE_Y - BORDER_Y - cBall.OUT_LINE)) 
	{
		vy *= -cBall.RETURN_SPEED;
		//座標を上に戻す
		pos.y += -radius / cBall.RADIUS_ADJUSMENT;
		// 跳ね返り対象を格納していたポインタを初期化する
		sBalls = nullptr;
	}
	// 位置を変更
	SetPosition(pos);
}

// 衝突判定
void BallDistinction::Collision()
{
	for (auto other : GetGame()->GetSortingBowls())
	{
		// ActiveObj以外はループを飛ばす
		// 自分とドラッグ中のボールには当たらないように設定
		// 直前に当たったボールには当たらないように設定
		if (other != this && !other->GetOnDrag() && other != sBalls) 
		{
			if (Intersect(*circleCol, *(other->GetCircle())) && other->GetState() == EActive)
			{
				// 直前に当たったボールを一時格納
				sBalls = other;

				// エネミーボールとの衝突判定
				if (other->ballPattern == pBalls.ENEMY_BALL)
				{
					// 当たった対象の半径に合わせてスケールを変更し、半径分カウントを下げる		
					float scale = (other->GetRadius()/cBall.SCALING) + 
						(this->GetRadius() / cBall.SCALING);
					other->SetScale(scale);
					GetGame()->CountDown(other->GetRadius());
					this->SetState(EPaused);
				}
				// 自分がエネミーボール以外の時は当たったら反射
				else if (this->ballPattern != pBalls.ENEMY_BALL)
				{
					// 方向速度を反転
					vx *= -cBall.RETURN_SPEED;
					vy *= -cBall.RETURN_SPEED;
				}
			}
		}
	}
}

// 再出現時リセット用
void BallDistinction::Reset()
{

	// 以下座標指定=========================================
	int rx, ry;
	// ENEMYの場合は初期位置変更
	if (GetThisBallPattern() == pBalls.ENEMY_BALL)
	{
		rx = 0; ry = 0;
	}
	else 
	{
		rx = GetRand(SIZE_X);
		ry = SIZE_X - BORDER_Y;
		while (!(this->SetyBall(rx, ry))) {
			rx = GetRand(SIZE_X);
			ry = SIZE_Y - BORDER_Y;
		}
	}
	// Ballの位置を変更
	Vector2 pos;
	pos.x = rx, pos.y = ry;
	SetPosition(pos);
	// 以上座標設定=========================================
	
	// 以下速度設定=========================================
	int rvx, rvy, defSpeed = 10;
	// スピードが0にならないように10を足す
	rvx = GetRand(100) + defSpeed;
	rvy = GetRand(100) + defSpeed;
	SetV(rvx, rvy);
	//初速度
	rightSpeed = vx;
	//初速度
	downSpeed = vy;
	// 以上速度設定=========================================

	// 半径設定
	RadiusRand();
	// フラグ初期化
	SetOnDrag(false);
	// フラグ初期化
	SetOnMouse(false);

	// サイズ設定		
	float scale = radius / cBall.SCALING;
	SetScale(scale);
	//衝突円作成
	circleCol = new CircleComponent(this);
	//衝突円（判定）の大きさを設定
	circleCol->SetRadius(cBall.COL_RADIUS);
#ifdef _DEBUG
	//衝突円（描写）の大きさ設定
	SetcRadius(cBall.COL_RADIUS);
#endif
}

// 移動挙動関数
Vector2 BallDistinction::Movement(Vector2 pos, float deltaTime)
{
	//速度更新
	rightSpeed = vx;
	downSpeed = vy;
	// deltaTime（１ループあたりの時間) x 方向のスピード=x方向の位置を更新
	pos.x += rightSpeed * deltaTime;
	pos.y += downSpeed * deltaTime;

	// マウスでドラッグされているときはアニメーションを止める
	if (onDrag)
		asc->SetAnimFPS(0);
	else
		asc->SetAnimFPS(ANIM_SPEED);
	return pos;
}

