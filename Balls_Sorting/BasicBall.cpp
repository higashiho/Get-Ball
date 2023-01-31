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
//位置を設定する関数（引数は座標値）　戻り値はウィンドウの範囲内
bool BasicBall::SetyBall(int x1, int y1) {
	bool flag = false;
	// 以下ウィンドウの範囲外の場合==========================

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

	// 以上ウィンドウ範囲外の場合===========================

	//初期座標
	x = x1;						
	y = y1;
	dispFlag = true;
	//ウィンドウの範囲内でtrueを返す
	flag = dispFlag;
	return flag;
}


//速度の設定関数
void BasicBall::SetV(int vx1, int vy1) {
	if (vx1 < cBall. MAX_VX) {
		vx = vx1;
	}
	else {
		//x方向速度の最大値
		vx = cBall.MAX_VX;	
	}
	if (vy1 < cBall.MAX_VY) {
		vy = vy1;
	}
	else {
		//y方向速度の最大値
		vy = cBall.MAX_VY;	
	}

}

// Display表示されているか取得関数
bool BasicBall::GetDispflag() {
	return dispFlag;
}

// 半径Random設定関数
void BasicBall::RadiusRand() {
	radius = GetRand(20) + cBall.MIN_RADIUS;
}

