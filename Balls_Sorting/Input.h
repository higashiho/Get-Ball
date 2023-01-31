#pragma once
#include "BasicBall.h"
#include "Game.h"
#include "BallDistinction.h"

const extern int SIZE_X, SIZE_Y;
class Input
{

public:
	Input();
	~Input();
	void CheckMouse(float* wx, float* wy, float r, class BasicBall*);
	void CheckMouseClick(class BasicBall*);
	void InitializationMaus();
	void MoveCursor(class Game* game, class BallDistinction* pBall);
	void MouseController(class Game* gmae, class BallDistinction* pBall);
protected:
	//�}�E�X����̃p�����[�^�[
	//�}�E�X�̃|�C���^�[���W
	int mouseX, mouseY;
	int* pMouseX, * pMouseY;
	//�}�E�X�̃|�C���^�[�����W
	int formerMouseX, formerMouseY;
	//��ʂ̒��S
	int centerX, centerY;
	// �{�[���������Ă��邩
	bool haveBall;
};

