#include "Input.h"
#include"DxLib.h"
#include <stdlib.h>
#include <iostream>

Input::Input()
{
	//マウス操作のパラメーター
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
//マウスのポインターオンチェック関数
void Input::CheckMouse(float* wx, float* wy, float r, BasicBall* balls) {
	// ボールの中心のx座標とマウスのｘ座標の差
	float dx = (mouseX - *wx);	
	// ボールの中心のy座標とマウスのy座標の差
	float dy = (mouseY - *wy);			
	float  tmp = dx * dx + dy * dy;
	// ボールの中心とマウスのポインターとの距離
	float distance = sqrt(tmp);	
	// ボールの半径より小さい場合
	if (distance < r) {					
		balls->SetOnMouse(true);
	}
	else {
		balls->SetOnMouse(false);
	}
}

// マウスのクリックをチェックする関数
void  Input::CheckMouseClick(BasicBall* balls) {
	
	balls->SetBallDrop(false);
	// ボタンが押されている
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		if (balls->GetOnMouse() && !haveBall) {
			// 左ボタンでドラッグされている
			balls->SetOnDrag(true);
			haveBall = true;
		}
	}
	else {
		// ドラッグ後離された場合のみ１フレームのみフラグを立てる
		if (balls->GetOnDrag())
			balls->SetBallDrop(true);
			// 左ボタンでドラッグされていない
		balls->SetOnDrag(false);
		haveBall = false;
	}

}

//マウスの初期化
void Input::InitializationMaus()
{
	//マウス座標の更新
	mouseX = centerX;	mouseY = centerY;
	formerMouseX = mouseX;	formerMouseY = mouseY;		
	//マウスのポインターの位置を設定
	SetMousePoint(mouseX, mouseY);
	//マウス表示
	SetMouseDispFlag(TRUE);				
}

// ボールを持った時の挙動
void Input::MoveCursor(class Game* game, class BallDistinction* pBall)
{
	if (pBall->GetOnDrag()) {
		Vector2 newPos;
		newPos.x = mouseX, newPos.y = mouseY;
		pBall->SetPosition(newPos);
	}
	else {
		// 指定地以外は速度を元に戻す
		// 指定地の場合は速度を０にする
		if (false) {
			float vx2 = 0;
			float vy2 = 0;
			pBall->SetV(vx2, vy2);
		}
	}
}

// ボール全体のコントローラー
void Input::MouseController(class Game* gmae, class BallDistinction* pBall)
{
	//現在のマウス座標を取得
	GetMousePoint(pMouseX, pMouseY);		
	Vector2 pos;
	//ボールの座標を設定
	pos = pBall->GetPosition();		
	CheckMouse(&pos.x, &pos.y, pBall->GetRadius(), pBall);
	//マウスの左クリックの状態を確認
	CheckMouseClick(pBall);						
	MoveCursor(gmae, pBall);
	//マウス座標の更新
	formerMouseX = mouseX;	formerMouseY = mouseY;		
}
