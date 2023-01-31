#include "EndScene.h"
EndScene::EndScene()
{
	centerX = SIZE_X / 2; centerY = SIZE_Y / 2;
}
EndScene::~EndScene()
{

}

// クリアシーン
GameSceneResultCode EndScene::Move(Game* game) {
	unsigned int collar;
	collar = GetColor(255, 255, 255);	//白を設定

	// タイトルシーンでのループ
	while (true)
	{
		// ゲーム更新メソッド
		game->UpdateGame();
		// 画像の表示メソッド
		game->GenerateOutput();
		DrawBox(1, SIZE_Y - BORDER_Y + 1, SIZE_X, SIZE_Y, GetColor(255, 0, 0), 1);
		DrawString(50, SIZE_Y - BORDER_Y, "Re Play = Enter", collar);
		DrawString(centerX + 50, SIZE_Y - BORDER_Y, "Game End = Escape", collar);
		if (CheckHitKey(KEY_INPUT_RETURN)) {
			ClearDrawScreen();
			// タイトルの背景を消して新しくメイン用のデータを読み込む
			game->UnloadData();
			return GAMESCENE_END_OK;
		}

		// エスケープキーでループを抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			game->GetSelectScene()->SetSceneFlag(GAMEPHASE_END);
			break;
		}
	}
	return GAMESCENE_DEFAULT;
}
