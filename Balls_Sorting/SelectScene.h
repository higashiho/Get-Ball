#pragma once
#include "IGameScene.h"
enum GamePhase {
	GAMEPHASE_INIT = 0,
	GAMEPHASE_RESET = 1,
	GAMEPHASE_TITLE = 0x010,
	GAMEPHASE_GAME = 0x100,
	GAMEPHASE_GAMEOVER = 0x200,
	GAMEPHASE_END = 0x300
};

enum GameSceneResultCode {
	GAMESCENE_DEFAULT = 0,
	GAMESCENE_END_OK = 1,
	GAMESCENE_END_TIMEOUT = 2,
	GAMESCENE_END_FAILURE = 3
};

class SelectScene 
{
public:
	~SelectScene();
	void ResetVariable(class Game* game);

	void SceneMove(class Game* game);

	// 以下代入用===================================
	void SetSceneFlag(GamePhase value) { eGamePhase = value; }
	// 以上代入用===================================
	
	// 以下取得用===================================
	GamePhase GetSceneFlag() { return eGamePhase; }
	// 以上取得用===================================
private:
	// スピード
	int SpeedX, SpeedY;
	// 連打防止用
	bool one;

	class IGameScene* pScene;		//	シーン
	GamePhase	eGamePhase;	//	状態変数
};

