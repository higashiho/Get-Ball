#include "InstanceBall.h"

InstanceBall::InstanceBall()
{
	instanceTimer = 0;
}

// YellowBallかRedBallを生成（オブジェクトが残っていて消えてる状態のときは再利用する）
void InstanceBall::Instance(Game* game)
{
	BasicBall* ballObj = nullptr;
	BallPattern pBalls;
	// イエローボールの場合
	{
		for (auto Balls : game->GetSortingBowls()) {
			// ステートがポーズのオブジェクトがいる場合それをActiveにして再利用
			if (Balls->GetState() == Actor::EPaused)
			{
				Balls->Reset();
				Balls->SetState(Actor::EActive);
				ballObj = Balls;
				break;
			}
		}
		if (ballObj == nullptr)
			new BallDistinction(game, pBalls.YELLOW_BALL);
	}
	// レッドボールの場合
	{
		for (auto Balls : game->GetSortingBowls()) {
			// ステートがポーズのオブジェクトがいる場合それをActiveにして再利用
			if (Balls->GetState() == Actor::EPaused)
			{
				Balls->SetState(Actor:: EActive);
				Balls->Reset();
				ballObj = Balls;
				break;
			}
		}
		if (ballObj == nullptr)
			new BallDistinction(game, pBalls.RED_BALL);
	}
}