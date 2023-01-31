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
	//マウス操作のパラメーター
	//マウスのポインター座標
	int mouseX, mouseY;
	int* pMouseX, * pMouseY;
	//マウスのポインター旧座標
	int formerMouseX, formerMouseY;
	//画面の中心
	int centerX, centerY;
	// ボールを持っているか
	bool haveBall;
};

