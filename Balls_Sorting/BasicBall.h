#pragma once
#include "DxLib.h"
#include "Actor.h"
#include <math.h>
#include <vector>

const extern int SIZE_X, SIZE_Y;		// ウィンドウのｘ方向、ｙ方向の大きさ
const extern int BORDER_Y;				// 情報表示領域のY座標(画面最下部から

// アニメーションの速度
#define ANIM_SPEED 5

// ボールの種類
struct  BallPattern{
	const int YELLOW_BALL = 0x00;
	const int RED_BALL = 0x01;
	const int ENEMY_BALL = 0x02;
};

// ボール用定数
struct ConstBall{
	// vx vy最大値
	const int MAX_VX = 200, MAX_VY = 200;		
	// ボールサイズ調整用
	const float SCALING = 40.0f;	
	// 画面端調整用
	const int OUT_LINE = 5;	
	// 速度反転用
	const int RETURN_SPEED = 1;		
	// 半径調整用
	const int RADIUS_ADJUSMENT = 2;
	// 半径最小値
	const int MIN_RADIUS = 10;			
	// 当たり判定の半径
	const float COL_RADIUS = 50.f;				
};

class BasicBall :public Actor {
public:
	//初期化
	BasicBall(class Game* game);

	virtual ~BasicBall();

	//衝突関数(周囲の境界に衝突した時の処理)
	virtual void Collision() = 0;
	//Ballの位置を更新する関数　deltaTime:ループを１回回る時間
	virtual void Update(float deltatime) = 0;
	//速度の設定関数
	void SetV(int vx1, int vy1);
	// 再度生成初期化用
	virtual void Reset() = 0;
	// radiusを設定するメソッド
	void RadiusRand();
	// 移動挙動関数
	virtual Vector2 Movement(Vector2, float) = 0;


	// 以下取得用===========================

	inline int Getx() { return x; }
	inline int Gety() { return y; }
	inline int GetRadius() { return radius; }
	inline int GetThisBallPattern() { return ballPattern; }
	//画面に表示されているのか
	inline bool GetDispflag();
	inline class CircleComponent* GetCircle() { return circleCol; }
	inline bool GetOnDrag() { return onDrag; }
	inline bool GetOnMouse() { return onMouse; }
	inline bool GetBallDrop() { return ballDrop; }

	// 以上取得用===========================


	/// 以下代入用==========================

	void SetRadius(float r) { radius = r; };
	//位置を設定する関数（引数は座標値）　戻り値はウィンドウの範囲内
	bool SetyBall(int x1, int y1);
	void SetOnDrag(bool flag) { onDrag = flag; }
	void SetOnMouse(bool flag) {onMouse = flag;}
	void SetBallDrop(bool flag) { ballDrop = flag; }

	/// 以上代入用==========================

protected:
	// ballの座標
	int x, y;	
	// ballの速度
	int vx, vy;				
	// ボールの半径
	int radius;				
	// 右方向のスピード
	float rightSpeed;		
	// 下方向のスピード
	float downSpeed;		
	//ディスプレイの中にいるか
	bool dispFlag;			
	//マウスのドラッグスイッチ
	bool onDrag;				
	//マウスのポインターオンスイッチ	
	bool onMouse;	
	// マウスがドラッグされて離されたフラグ
	bool ballDrop;
	//衝突円へのポインター
	class CircleComponent* circleCol;		
	// 自身のボールパターン
	int ballPattern;
	// 定数使用用
	ConstBall cBall;
	BallPattern pBalls;
	// 当たった対象格納用ポインタ
	class BallDistinction* sBalls;

	// アニメーションクラスポインタ
	
	class AnimSpriteComponent* asc;

};
