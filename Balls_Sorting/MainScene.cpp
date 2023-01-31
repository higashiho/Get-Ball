#include "MainScene.h"

MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}

// メインシーン関数
GameSceneResultCode MainScene::Move(Game* game)
{
	// ゲームループ
	game->RunLoop();

	ClearDrawScreen();
	// タイトルの背景を消して新しくメイン用のデータを読み込む
	game->UnloadData();

	// RunLoopを抜けたらリザルトに変える
	return GAMESCENE_END_OK;
}
