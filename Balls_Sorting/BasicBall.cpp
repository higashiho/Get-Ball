#include "BasicBall.h"
#include "Game.h"

BasicBall::BasicBall(Game* game):Actor(game)
{
	x = 0;						
	y = 0;						
	vx = 0;						
	vy = 0;						
	radius = 20;				
	rightSpeed = 0;				
	downSpeed = 0;	
	ballPattern = 0;
	circleCol = nullptr;
	dispFlag = true;
	onDrag = false;
	onMouse = false;
	ballDrop = false;
	sBalls = nullptr;
}


BasicBall::~BasicBall()
{
}
//�ʒu��ݒ肷��֐��i�����͍��W�l�j�@�߂�l�̓E�B���h�E�͈͓̔�
bool BasicBall::SetyBall(int x1, int y1) {
	bool flag = false;
	// �ȉ��E�B���h�E�͈̔͊O�̏ꍇ==========================

	if ((x1 - radius) < cBall.OUT_LINE) {				
		return  flag;
	}
	if ((x1 + radius) > (SIZE_X - cBall.OUT_LINE)) {
		return flag;
	}

	if ((y1 - radius) < cBall.OUT_LINE) {				
		return flag;
	}
	if ((y1 + radius) > (SIZE_X - cBall.OUT_LINE)) {	
		return flag;
	}

	// �ȏ�E�B���h�E�͈͊O�̏ꍇ===========================

	//�������W
	x = x1;						
	y = y1;
	dispFlag = true;
	//�E�B���h�E�͈͓̔���true��Ԃ�
	flag = dispFlag;
	return flag;
}


//���x�̐ݒ�֐�
void BasicBall::SetV(int vx1, int vy1) {
	if (vx1 < cBall. MAX_VX) {
		vx = vx1;
	}
	else {
		//x�������x�̍ő�l
		vx = cBall.MAX_VX;	
	}
	if (vy1 < cBall.MAX_VY) {
		vy = vy1;
	}
	else {
		//y�������x�̍ő�l
		vy = cBall.MAX_VY;	
	}

}

// Display�\������Ă��邩�擾�֐�
bool BasicBall::GetDispflag() {
	return dispFlag;
}

// ���aRandom�ݒ�֐�
void BasicBall::RadiusRand() {
	radius = GetRand(20) + cBall.MIN_RADIUS;
}

