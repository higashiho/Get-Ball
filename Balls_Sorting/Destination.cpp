#include "Destination.h"
#include "BoxComponent.h"

#include "AnimSpriteComponent.h"

Destination::Destination(Game* game, Vector2 pos,int num):Actor(game)
{
	goalNumber = num;
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);	// Animation�X�v���C�g���쐬���Ă��̃|�C���^�[����
	std::vector<int> anims = {									// Animation �̊e�t���[���̃n���h����vector�^�z��ɑ��
		game->GetTexture("Image/Goal.png"),
	};
	asc->SetAnimTextures(anims);// AnimationComponent �N���X�̃��\�b�h�Ŋe�t���[���̃n���h����o�^
	asc = nullptr;
	delete asc;
	SetPosition(pos);
	Vector2 max1, min1, size;
	// ���ۂ̋�`�T�C�Y
	size.x = 240.f; size.y = 240.f;

	// �Փˋ�`�̍���̂̍��W�ƉE���̍��W
	max1.x = pos.x + GetScale() * size.x / 2.0f;
	max1.y = pos.y + GetScale() * size.y / 2.0f;
	min1.x = pos.x - GetScale() * size.x / 2.0f;
	min1.y = pos.y - GetScale() * size.y / 2.0f;

	// �Փˋ�`�iBoxComponent�j�̒ǉ�
	boxCol = new BoxComponent(this);
	boxCol->SetPoint(max1, min1);
	SetBsize(size);
}

Destination::~Destination()
{
	SAFE_DELETE(boxCol);
}
// �S�̋���
void Destination::UpdateActor(float deltaTime)
{
	Collision(goalNumber);
}

// �����蔻��
void Destination::Collision(int patternBall)
{
	for (auto other : GetGame()->GetSortingBowls())
	{
		if(other == nullptr)
			continue;
		// ���������{�[�����h���b�O�㗣���ꂽ�ꍇ�̂ݏ���
		if (other->GetBallDrop())
		{
			if (Intersect(*(other->GetCircle()), *boxCol) && other->GetState() == EActive)
				// �����ꂽ�̂��w��̂̏ꍇ
				if (other->GetThisBallPattern() == patternBall)
				{
					GetGame()->CountUp((UINT)other->GetRadius());
					other->SetState(EPaused);
				}
			// ����ȊO�̏ꍇ
				else
					GetGame()->SetGameOverFlag(true);
			break;
		}
	}
}