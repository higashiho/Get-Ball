#include "BallDistinction.h"
#include "AnimSpriteComponent.h"
#include"CircleComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Input.h"
#include "DxLib.h"

// �R���X�g���N�^
BallDistinction::BallDistinction(Game* game, int bowlsNumber) :BasicBall(game)
{
	// �ȉ��\���ݒ�=========================================
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
	// �ȏ�\���ݒ�=========================================
	// AnimationComponent �N���X�̃��\�b�h��1�t���[���̃n���h����o�^
	asc->SetAnimTextures(anims);		


	// �����ݒ�֐�
	Reset();
	//�Q�[���V�[���ɒǉ�
	game->AddSortingBowls(this);						
}

// �f�X�g���N�^
BallDistinction::~BallDistinction()
{
	GetGame()->RemoveSortingBowls(this);
	/*
	SAFE_DELETE(pOnDrag);
	SAFE_DELETE(pOnMouse);
	SAFE_DELETE(pBallDrop);*/
}

// �S�̋���
void BallDistinction::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// �����蔻��
	Collision();
	// �ړ�
	Update(deltaTime);

	// �}�E�X�|�C���^�[����
	// �G�l�~�[�{�[���͎��ĂȂ��悤�ɂ���
#ifdef _DEBUG
	GetGame()->GetInput()->MouseController(GetGame(), this);
#else
	if (this->ballPattern != pBalls.ENEMY_BALL)
		GetGame()->GetInput()->MouseController(GetGame(), this);
#endif
		
}

// �X�V����
void BallDistinction::Update(float deltaTime) 
{
	// ���݂̈ʒu���擾
	Vector2 pos = GetPosition();

	// �ړ�
	pos = Movement(pos, deltaTime);

	//���͂̋��E�Ƃ̏Փ�
	//�E�B���h�E�͈͓����ǂ���
	if ((pos.x - radius) < cBall.OUT_LINE)
	{
		//x�������x�𔽓]
		vx *= -cBall.RETURN_SPEED;
		//���W���E�ɖ߂�
		pos.x += radius / cBall.RADIUS_ADJUSMENT;

		// ���˕Ԃ�Ώۂ��i�[���Ă����|�C���^������������
		sBalls = nullptr;
	}
	if ((pos.x + radius) > (SIZE_X - cBall.OUT_LINE)) 
	{
		vx *= -cBall.RETURN_SPEED;
		//���W�����ɖ߂�
		pos.x += -radius / cBall.RADIUS_ADJUSMENT;
		// ���˕Ԃ�Ώۂ��i�[���Ă����|�C���^������������
		sBalls = nullptr;
	}
	if ((pos.y - radius) < cBall.OUT_LINE) 
	{
		//y�������x�𔽓]
		vy *= -cBall.RETURN_SPEED;					
		//���W�����ɖ߂�
		pos.y += radius / cBall.RADIUS_ADJUSMENT;
		// ���˕Ԃ�Ώۂ��i�[���Ă����|�C���^������������
		sBalls = nullptr;
	}
	if ((pos.y + radius) > (SIZE_Y - BORDER_Y - cBall.OUT_LINE)) 
	{
		vy *= -cBall.RETURN_SPEED;
		//���W����ɖ߂�
		pos.y += -radius / cBall.RADIUS_ADJUSMENT;
		// ���˕Ԃ�Ώۂ��i�[���Ă����|�C���^������������
		sBalls = nullptr;
	}
	// �ʒu��ύX
	SetPosition(pos);
}

// �Փ˔���
void BallDistinction::Collision()
{
	for (auto other : GetGame()->GetSortingBowls())
	{
		// ActiveObj�ȊO�̓��[�v���΂�
		// �����ƃh���b�O���̃{�[���ɂ͓�����Ȃ��悤�ɐݒ�
		// ���O�ɓ��������{�[���ɂ͓�����Ȃ��悤�ɐݒ�
		if (other != this && !other->GetOnDrag() && other != sBalls) 
		{
			if (Intersect(*circleCol, *(other->GetCircle())) && other->GetState() == EActive)
			{
				// ���O�ɓ��������{�[�����ꎞ�i�[
				sBalls = other;

				// �G�l�~�[�{�[���Ƃ̏Փ˔���
				if (other->ballPattern == pBalls.ENEMY_BALL)
				{
					// ���������Ώۂ̔��a�ɍ��킹�ăX�P�[����ύX���A���a���J�E���g��������		
					float scale = (other->GetRadius()/cBall.SCALING) + 
						(this->GetRadius() / cBall.SCALING);
					other->SetScale(scale);
					GetGame()->CountDown(other->GetRadius());
					this->SetState(EPaused);
				}
				// �������G�l�~�[�{�[���ȊO�̎��͓��������甽��
				else if (this->ballPattern != pBalls.ENEMY_BALL)
				{
					// �������x�𔽓]
					vx *= -cBall.RETURN_SPEED;
					vy *= -cBall.RETURN_SPEED;
				}
			}
		}
	}
}

// �ďo�������Z�b�g�p
void BallDistinction::Reset()
{

	// �ȉ����W�w��=========================================
	int rx, ry;
	// ENEMY�̏ꍇ�͏����ʒu�ύX
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
	// Ball�̈ʒu��ύX
	Vector2 pos;
	pos.x = rx, pos.y = ry;
	SetPosition(pos);
	// �ȏ���W�ݒ�=========================================
	
	// �ȉ����x�ݒ�=========================================
	int rvx, rvy, defSpeed = 10;
	// �X�s�[�h��0�ɂȂ�Ȃ��悤��10�𑫂�
	rvx = GetRand(100) + defSpeed;
	rvy = GetRand(100) + defSpeed;
	SetV(rvx, rvy);
	//�����x
	rightSpeed = vx;
	//�����x
	downSpeed = vy;
	// �ȏ㑬�x�ݒ�=========================================

	// ���a�ݒ�
	RadiusRand();
	// �t���O������
	SetOnDrag(false);
	// �t���O������
	SetOnMouse(false);

	// �T�C�Y�ݒ�		
	float scale = radius / cBall.SCALING;
	SetScale(scale);
	//�Փˉ~�쐬
	circleCol = new CircleComponent(this);
	//�Փˉ~�i����j�̑傫����ݒ�
	circleCol->SetRadius(cBall.COL_RADIUS);
#ifdef _DEBUG
	//�Փˉ~�i�`�ʁj�̑傫���ݒ�
	SetcRadius(cBall.COL_RADIUS);
#endif
}

// �ړ������֐�
Vector2 BallDistinction::Movement(Vector2 pos, float deltaTime)
{
	//���x�X�V
	rightSpeed = vx;
	downSpeed = vy;
	// deltaTime�i�P���[�v������̎���) x �����̃X�s�[�h=x�����̈ʒu���X�V
	pos.x += rightSpeed * deltaTime;
	pos.y += downSpeed * deltaTime;

	// �}�E�X�Ńh���b�O����Ă���Ƃ��̓A�j���[�V�������~�߂�
	if (onDrag)
		asc->SetAnimFPS(0);
	else
		asc->SetAnimFPS(ANIM_SPEED);
	return pos;
}

