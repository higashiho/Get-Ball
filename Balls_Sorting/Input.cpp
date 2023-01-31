#include "Input.h"
#include"DxLib.h"
#include <stdlib.h>
#include <iostream>

Input::Input()
{
	//�}�E�X����̃p�����[�^�[
	mouseX = 0;
	mouseY = 0;			
	formerMouseX = 0;
	formerMouseY = 0;
	centerX = SIZE_X / 2; centerY = SIZE_Y / 2;
	haveBall = false;

	pMouseX = &mouseX, pMouseY = &mouseY;
}

Input::~Input()
{
}
//�}�E�X�̃|�C���^�[�I���`�F�b�N�֐�
void Input::CheckMouse(float* wx, float* wy, float r, BasicBall* balls) {
	// �{�[���̒��S��x���W�ƃ}�E�X�̂����W�̍�
	float dx = (mouseX - *wx);	
	// �{�[���̒��S��y���W�ƃ}�E�X��y���W�̍�
	float dy = (mouseY - *wy);			
	float  tmp = dx * dx + dy * dy;
	// �{�[���̒��S�ƃ}�E�X�̃|�C���^�[�Ƃ̋���
	float distance = sqrt(tmp);	
	// �{�[���̔��a��菬�����ꍇ
	if (distance < r) {					
		balls->SetOnMouse(true);
	}
	else {
		balls->SetOnMouse(false);
	}
}

// �}�E�X�̃N���b�N���`�F�b�N����֐�
void  Input::CheckMouseClick(BasicBall* balls) {
	
	balls->SetBallDrop(false);
	// �{�^����������Ă���
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		if (balls->GetOnMouse() && !haveBall) {
			// ���{�^���Ńh���b�O����Ă���
			balls->SetOnDrag(true);
			haveBall = true;
		}
	}
	else {
		// �h���b�O�㗣���ꂽ�ꍇ�݂̂P�t���[���̂݃t���O�𗧂Ă�
		if (balls->GetOnDrag())
			balls->SetBallDrop(true);
			// ���{�^���Ńh���b�O����Ă��Ȃ�
		balls->SetOnDrag(false);
		haveBall = false;
	}

}

//�}�E�X�̏�����
void Input::InitializationMaus()
{
	//�}�E�X���W�̍X�V
	mouseX = centerX;	mouseY = centerY;
	formerMouseX = mouseX;	formerMouseY = mouseY;		
	//�}�E�X�̃|�C���^�[�̈ʒu��ݒ�
	SetMousePoint(mouseX, mouseY);
	//�}�E�X�\��
	SetMouseDispFlag(TRUE);				
}

// �{�[�������������̋���
void Input::MoveCursor(class Game* game, class BallDistinction* pBall)
{
	if (pBall->GetOnDrag()) {
		Vector2 newPos;
		newPos.x = mouseX, newPos.y = mouseY;
		pBall->SetPosition(newPos);
	}
	else {
		// �w��n�ȊO�͑��x�����ɖ߂�
		// �w��n�̏ꍇ�͑��x���O�ɂ���
		if (false) {
			float vx2 = 0;
			float vy2 = 0;
			pBall->SetV(vx2, vy2);
		}
	}
}

// �{�[���S�̂̃R���g���[���[
void Input::MouseController(class Game* gmae, class BallDistinction* pBall)
{
	//���݂̃}�E�X���W���擾
	GetMousePoint(pMouseX, pMouseY);		
	Vector2 pos;
	//�{�[���̍��W��ݒ�
	pos = pBall->GetPosition();		
	CheckMouse(&pos.x, &pos.y, pBall->GetRadius(), pBall);
	//�}�E�X�̍��N���b�N�̏�Ԃ��m�F
	CheckMouseClick(pBall);						
	MoveCursor(gmae, pBall);
	//�}�E�X���W�̍X�V
	formerMouseX = mouseX;	formerMouseY = mouseY;		
}
