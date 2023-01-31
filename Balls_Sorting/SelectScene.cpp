#include "SelectScene.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "EndScene.h"

SelectScene::~SelectScene()
{
	SAFE_DELETE(pScene);
}


// リセット関数
void SelectScene::ResetVariable(Game* game)
{
	// 今の時間を設定
	game->SetStartTime(GetNowCount());
	// カウント初期化
	game->SetCount(START_COUNT);
	// ゲームオーバーフラグ初期化
	game->SetGameOverFlag(false);


	// タイトルの背景を消して新しくメイン用のデータを読み込む
	game->UnloadData();
	game->LoadData(eGamePhase);

}

// シーン挙動
void SelectScene::SceneMove(Game* game)
{
	GameSceneResultCode rc = GAMESCENE_DEFAULT;

	switch (eGamePhase) {
	case GAMEPHASE_INIT:
		eGamePhase = GAMEPHASE_RESET;

	// 初期リセット
	case GAMEPHASE_RESET:
		SAFE_DELETE(pScene);
		pScene = new TitleScene();
		eGamePhase = GAMEPHASE_TITLE;
		ResetVariable(game);
		game->LoadData(eGamePhase);

	// タイトルシーン
	case GAMEPHASE_TITLE:
		if (pScene != NULL)
			rc = pScene->Move(game);
		if (rc == GAMESCENE_DEFAULT)
			break;

		SAFE_DELETE(pScene);
		pScene = new MainScene();
		eGamePhase = GAMEPHASE_GAME;
		game->LoadData(eGamePhase);

	// インゲーム
	case GAMEPHASE_GAME:
		if (pScene != NULL)
			rc = pScene->Move(game);
		if (rc == GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(pScene);
		pScene = new EndScene();
		eGamePhase = GAMEPHASE_GAMEOVER;
		game->LoadData(eGamePhase);

	// リザルトシーン
	case GAMEPHASE_GAMEOVER:

		if (pScene != NULL)
			rc = pScene->Move(game);
		if (rc == GAMESCENE_DEFAULT)
			break;
		eGamePhase = GAMEPHASE_RESET;
	default:
		break;
	}
}
