#pragma once
#include "BallDistinction.h"
#include "BasicBall.h"
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include "InstanceBall.h"
#include "Input.h"
#include "SelectScene.h"

// タイマーを減らす間隔
#define TIMER_COUNT 1
// タイマーの初期値
#define MAX_SPONE_TIMER 100
#define MAX_COL_TIMER 10
// ゴールのpos.x調整用
#define ADJUSMENT_POS_X 100
// ゴールの識別用
#define YELLOW_BALL_GOAL 0
#define RED_BALL_GOAL 1
// カウント初期地
#define START_COUNT 100
// 半径得点変化用(半径最大値+5)
#define COUNT_CHANGE_RATIOS 35
// ループ遅延時間
#define WAIT_TIME 16
// deltaTime最大値
#define MAX_DELTA_TIME 0.05f
// タイマー調整用
#define ADJUST_TIMER 1000
// 背景スクロールスピード
#define SCROLL_LOW_SPEED 100
#define SCROLL_HIGH_SPEED 200

// ポインタDelete用
#define SAFE_DELETE(o)  if (o){ delete (o); o = NULL; }

// 画像ファイル名とそのハンドルを持つ構造体
struct Dx_Texture {
	// 画像のファイル名
	std::string filename;	
	// 画像のハンドル（Dxlibで使用するもの)
	int handle;					
};
class Game {
public:
	bool Initialize();
	void DisplayTime();
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void UpdateGame();
	void UnloadData();
	int GetTexture(const std::string& fileName);
	void Shutdown();
	void RunLoop();		
	void JudgCount();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	void AddSortingBowls(class BallDistinction* ast);
	void RemoveSortingBowls(class BallDistinction* ast);
	void GenerateOutput();
	// シーン画像データを読み込むメソッドの定義
	void LoadData(const int);
	void BackgroundLoading(std::string str, std::string str2, float speed);

	Game();
	~Game();

	// 以下代入用======================================

	void SetStartTime(int value) { startTime = value; }
	void SetGameOverFlag(bool flag) { gameOver = flag; }
	void SetCount(float value) { count = value; }
	// 仕分け成功時にカウントを増やす
	void CountUp(UINT radius) { count += ~radius + COUNT_CHANGE_RATIOS; }
	// エネミーボールに当たった時半径分カウントを減らす
	void CountDown(float radius) { count -= radius; }

	// 以上代入用======================================

	// 以下取得用======================================

	inline std::vector<class BallDistinction*>& GetSortingBowls() { return ballDistinctions; }
	inline std::vector<class Actor*>& GetActors() { return actors; }
	inline class Input* GetInput() { return input; }
	inline class SelectScene* GetSelectScene() { return selectScene; }

	// 以上取得用======================================

private:
	//画面の中心
	int centerX, centerY;
	//ゲーム時間
	int startTime;
	//プレイ時間
	int playTime;
	//ゲームスタートからの時間を保持する変数
	int time;
	// Actor情報を直ぐに更新するかどうかのフラグ
	bool updatingActors;
	// ゲーム開始からの経過時間
	float  ticksCount;
	// 生成フラグ
	bool instansFlag;
	// 生成間隔
	int instansTimer;
	// 仕分け成功カウント
	int count;
	// ゲームオーバーフラグ
	bool gameOver;

	// 画像データ(ファイル名とそのハンドルをセット)にした動的配列
	std::unordered_map<std::string, int> textures;

	// 以下配列ポインタ================================

	// ボール格納用配列ポインタ
	std::vector<class BallDistinction*>ballDistinctions;
	// シーンに登録するActorクラスの動的配列のポインタ
	std::vector<class Actor*> actors;
	// 登録する予定のActorクラスの動的配列のポインタ
	std::vector<class Actor*> pendingActors;
	// シーンに登録するスプライトのポインタ
	std::vector<class SpriteComponent*> sprites;

	// 以上配列ポインタ================================

	// 以下クラスポインタ===============================

	class Input* input;
	class InstanceBall* instance;
	class SelectScene* selectScene;

	// 以上クラスポインタ===============================

	// 入力のメソッド
	void processInput();
	// 次生成できるまでのカウンター
	bool waitInstans(bool*, int*);

};

