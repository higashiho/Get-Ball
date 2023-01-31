#include "Game.h"
#include "SelectScene.h"



// ウインドウのサイズ
const int SIZE_X = 1000, SIZE_Y = 750;
//情報表示領域のy座標
const int BORDER_Y = 70;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;
	if (game.Initialize())
	{
		//以下初期化処理====================================

		ClearDrawScreen();
		game.GetInput()->InitializationMaus();

		// 以上初期化処理===================================

		// 以下文字列表示初期設定===========================

		//文字の大きさ
		SetFontSize(50);
		//文字のフォント
		ChangeFont("Impact");
		//文字表示設定
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);

		// 以上文字列表示設定===============================


		// 以下ゲームメインループ===========================

		while (!ProcessMessage())
		{
			game.GetSelectScene()->SceneMove(&game);
			// sceneFlagがEndの状態で抜けてきたらゲーム終了
			if (game.GetSelectScene()->GetSceneFlag() == END)
				break;
		}

		// 以上メインループ=================================
	}

	// 以下ゲーム終了後の処理===============================

	ClearDrawScreen();
	unsigned int Cr;
	Cr = GetColor(255, 255, 255);	//白を設定
	DrawString(250, 240 - 32, "Thank you for Playing", Cr);
	game.Shutdown();	// 画像削除関数

	// 以上ゲーム終了後の処理===============================

	return 0;
}