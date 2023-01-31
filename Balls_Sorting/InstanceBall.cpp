#include "InstanceBall.h"

InstanceBall::InstanceBall()
{
	instanceTimer = 0;
}

// YellowBall��RedBall�𐶐��i�I�u�W�F�N�g���c���Ă��ď����Ă��Ԃ̂Ƃ��͍ė��p����j
void InstanceBall::Instance(Game* game)
{
	BasicBall* ballObj = nullptr;
	BallPattern pBalls;
	// �C�G���[�{�[���̏ꍇ
	{
		for (auto Balls : game->GetSortingBowls()) {
			// �X�e�[�g���|�[�Y�̃I�u�W�F�N�g������ꍇ�����Active�ɂ��čė��p
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
	// ���b�h�{�[���̏ꍇ
	{
		for (auto Balls : game->GetSortingBowls()) {
			// �X�e�[�g���|�[�Y�̃I�u�W�F�N�g������ꍇ�����Active�ɂ��čė��p
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