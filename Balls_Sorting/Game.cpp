#include "Game.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "BasicBall.h"
#include "BGSpriteComponent.h"
#include"BallDistinction.h"
#include "Destination.h"
#include "SelectScene.h"

#include<fstream>
						

Game::Game()
	: updatingActors(false)
{
	playTime = 0;			
	ticksCount = 0;		
	time = 0.f;	
	input = new Input;
	instance = new InstanceBall;
	selectScene = new SelectScene();
	centerX = SIZE_X / 2; centerY = SIZE_Y / 2;
	updatingActors = false;
	startTime = 0;
	instansFlag = true;
	instansTimer = 100;
	count = START_COUNT;
	gameOver = false;
}

Game::~Game()
{
	SAFE_DELETE(instance);
	SAFE_DELETE(selectScene);
	SAFE_DELETE(input);
}

// Gameクラスのメソッドの定義(初期化メソッド)
bool Game::Initialize()
{
	if (DxLib_Init() == -1)				// ＤＸライブラリ初期化処理
	{
		return false;					// エラーが起きたら直ちに終了
	}
	SetGraphMode(SIZE_X, SIZE_Y, 32);		// 画面の大きさをSizeX × SizeY に設定する
	ChangeWindowMode(TRUE);				// ウインドウモード

	ticksCount = GetNowCount();

	return true;
}

// ゲームのメインループメソッド
void Game::RunLoop()
{
	while (!gameOver)
	{
		// タイマー
		DisplayTime();
		// 入力メソッド
		processInput();
		// ゲーム更新メソッド
		UpdateGame();
		// 画像の表示メソッド
		GenerateOutput();
		// カウントが0になったらループ終了メソッド
		JudgCount();
		// タブキーを押したらリザルトへ移動
		if (CheckHitKey(KEY_INPUT_TAB)) { break; }
#ifdef _DEBUG
		// エスケープキーを押すとゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) { break; }
#endif
	}
}

// 入力のメソッドの定義
void Game::processInput()
{
#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		instance->Instance(this);
	}
#endif
	if (waitInstans(&instansFlag, &instansTimer)) {
		try {
			// ゲームスタートからの時間
			time = GetNowCount() - startTime;
			//残り時間の計算
			int dis = playTime * ADJUST_TIMER + time;
			if (((dis / ADJUST_TIMER) & 1) == 0)
			{
				instansFlag = false;
				instance->Instance(this);
			}
		}

		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
	}
}

// ゲームの更新メソッドの定義
void Game::UpdateGame()
{
	// 待機時間(16ms）設定
	WaitTimer(WAIT_TIME);
	// １ループ時間の計算
	float deltaTime = (GetNowCount() - ticksCount) / ADJUST_TIMER;
	if (deltaTime > MAX_DELTA_TIME)
	{
		deltaTime = MAX_DELTA_TIME;
	}
	ticksCount = GetNowCount();

	//シーンに登場するオブジェクト(Actorクラスを継承)を更新
	updatingActors = true;
	for (auto actor : actors)
	{
		actor->Update(deltaTime);
	}

	// シーンに登場するオブジェクトを追加する場合のループ
	for (auto pending : pendingActors)
	{
		// vector型配列の更新メソッド
		actors.emplace_back(pending);		
	}
	// vector型配列をクリア(全消去)メソッド
	pendingActors.clear();					

	// 死んだアクターをテンポラリベクターに追加
	// vector型配列(Actorクラスのポインターをためる配列)
	std::vector<Actor*> deadActors;					
	for (auto actor : actors)
	{
		// Actorクラスのオブジェクトの状態がEDeadの場合
		if (actor->GetState() == Actor::EDead)		
		{
			// vector型配列の更新メソッド
			deadActors.emplace_back(actor);			
		}
	}

	// Actorクラスのオブジェクトの状態EDeadのすべてを消去
	for (auto actor : deadActors)
	{
		//要素すべてを消去(ｖector型配列内を消去)
		delete actor;			
	}

}

// シーンの全体を描画するメソッド
void Game::GenerateOutput()
{
	// 画面クリア
	ClearDrawScreen();						
	// Box画面クリア
	DrawBox(0, 0, SIZE_X, SIZE_Y, GetColor(0, 0, 0), 1);

	// すべてのスプライトについて描画順を考慮して描く
	for (auto sprite : sprites)
	{
		// 背景を含めて画像を描画するメソッド
		sprite->Draw();					
	}

}

// シーン画像データを読み込むメソッドの定義
void Game::LoadData(const int noeScene)
{

	Vector2 pos, pos2;
	pos.x = ADJUSMENT_POS_X, pos.y = centerY - BORDER_Y;
	pos2.x = SIZE_X - ADJUSMENT_POS_X, pos2.y = centerY - BORDER_Y;
	BallPattern pBalls;
	switch (noeScene)
	{
		// タイトルでのデータ
	case TITEL_SCENE:
		BackgroundLoading("image/Title.jpg", "image/Title_flip.jpg", SCROLL_LOW_SPEED);
		BackgroundLoading("image/Dot.png", "image/Dot.png", SCROLL_HIGH_SPEED);
		break;
		// メインシーンでのデータ
	case MAIN_SCENE:
		BackgroundLoading("image/BackSky.jpg", "image/BackSky_flip.jpg", SCROLL_HIGH_SPEED);
		BackgroundLoading("image/BackHome.png", "image/BackHome_flip.png", SCROLL_LOW_SPEED);

		new Destination(this, pos, YELLOW_BALL_GOAL);
		new Destination(this, pos2, RED_BALL_GOAL);
		new BallDistinction(this, pBalls.ENEMY_BALL);
		break;
	case RESULT_SCENE:
		BackgroundLoading("image/Result.jpg", "image/Result_flip.jpg", SCROLL_LOW_SPEED);
		BackgroundLoading("image/Dot.png", "image/Dot.png", SCROLL_HIGH_SPEED);
		break;
	default:
		break;
	}
}

// 背景の読み込みメソッド
void Game::BackgroundLoading(std::string str,std::string str2 ,float speed)
{
	// 背景用のアクタを作成する
	Actor* temp = new Actor(this);
	// 中心に表示、y座標は下にテキストがあるため少し上に設定
	temp->SetPosition(Vector2(500.0f, 325.0f));

	// 背景のスプライトを作成
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 50);
	// 背景の大きさ
	bg->SetScreenSize(Vector2(SIZE_X, SIZE_Y));
	std::vector<int> bgtexs = {
		// 背景画像のハンドル(整数型)を登録
		GetTexture(str),
		GetTexture(str2),
	};

	// mBGTexures 登録(ハンドルの配列をスプライトに登録)
	bg->SetBGTextures(bgtexs);
	// スプライトのスクロールスピードの設定
	bg->SetScrollSpeed(-speed);

}
// ゲーム終了時の画像データの消去メソッド
void Game::UnloadData()
{
	// ゲームに登録されているActorが全て消去するまでループを続ける
	while (!actors.empty())
	{
		// ゲームに登録されているActorの最後を見つけて消去する
		delete actors.back();			
	}
	// 背景画像のデータを消去
	textures.clear();					
}

// 画像データを実際に読み込んでそのハンドル(整数)を返すメソッド
int Game::GetTexture(const std::string& fileName)
{
	int tex = -1;
	// Is the texture already in the map?
	auto iter = textures.find(fileName);
	if (iter != textures.end())
	{
		tex = iter->second;
	}
	else
	{
		// 画像のハンドルを返す
		tex = LoadGraph(fileName.c_str());
		if (tex == -1)
		{
			std::cout << "Failed to load texture file " << fileName << "\n";
			return -1;
		}
		// map型配列を更新(配列に２つの値をセットで登録)
		textures.emplace(fileName.c_str(), tex);			
	}
	// handleを返す
	return tex;				
}

// ゲームの終了メソッドの定義
void Game::Shutdown()
{
	// シーンのActorおよび画像データの消去(解放）
	UnloadData();			

	WaitKey();          //キーの入力待ち
	// ＤＸライブラリ使用の終了処理
	DxLib_End();			

}

// ゲームシーンにActorを追加するメソッド定義
void Game::AddActor(Actor* actor)
{
	// Actorを登録するタイミングが来ているかどうか
	if (updatingActors)						
	{
		// 次回登録リストに追加
		pendingActors.emplace_back(actor);		
	}
	else
	{
		// シーンに登録
		actors.emplace_back(actor);			
	}
}

// ゲームシーンにあるActorを削除するメソッド定義
void Game::RemoveActor(Actor* actor)
{
	// 待機リストにあるかどうかを検索して見つかれば消去
	auto iter = std::find(pendingActors.begin(), pendingActors.end(), actor);
	if (iter != pendingActors.end())
	{

		std::iter_swap(iter, pendingActors.end() - 1);
		pendingActors.pop_back();
	}

	// シーンにある場合に見つかれば消去
	iter = std::find(actors.begin(), actors.end(), actor);
	if (iter != actors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, actors.end() - 1);
		actors.pop_back();
	}
}

// スプライトを追加するメソッド
void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = sprites.begin();
	for (;
		iter != sprites.end();
		++iter)
	{
		// スプライトの描画順を決める
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	// Inserts element before position of iterator
	sprites.insert(iter, sprite);
}
//スプライトの消去メソッドの定義
void Game::RemoveSprite(SpriteComponent* sprite)
{
	// スプライトを探す
	auto iter = std::find(sprites.begin(), sprites.end(), sprite);
	// スプライトの消去
	sprites.erase(iter);
}

// ボールの生成メソッドの定義
void Game::AddSortingBowls(BallDistinction* other)
{
	ballDistinctions.emplace_back(other);
}

// ボールの消去メソッドの定義
void Game::RemoveSortingBowls(BallDistinction* other)
{
	auto iter = std::find(ballDistinctions.begin(),
		ballDistinctions.end(), other);
	if (iter != ballDistinctions.end())
	{
		ballDistinctions.erase(iter);
	}
}

//ゲーム時間とボールの消失した数を表示する関数
void Game::DisplayTime() {		
	// ゲームスタートからの時間
	time = GetNowCount() - startTime;
	//残り時間の計算
	int dis = playTime * ADJUST_TIMER + time;

	//表示領域を指定色でクリアする
	DrawBox(1, SIZE_Y - BORDER_Y + 1, SIZE_X, SIZE_Y, GetColor(0, 255, 0), 1);
	DrawFormatString(centerX + 200, SIZE_Y - BORDER_Y + 2, GetColor(255, 255, 255), "Time=%d", dis / ADJUST_TIMER);
	DrawFormatString(0, SIZE_Y - BORDER_Y + 2, GetColor(255, 255, 255), "Count=%d", count);
}

// ボール生成された場合一定時間後にフラグをonにする関数
bool Game::waitInstans(bool* flag, int* timer)
{
	if (flag == nullptr || timer ==  nullptr)
		throw std::exception("error!");

	if (!*flag)
	{
		*timer -= TIMER_COUNT;
		// flagが折れている状態ででtimerが０の場合のみtrueを変えす
		if (*timer <= 0)
		{
			*flag = true;
			*timer = MAX_SPONE_TIMER;
			return true;
		}
		return false;
	}
	else
		return true;

}

// countが０になったらゲームループから抜け出す処理
void Game::JudgCount()
{
	if (count <= 0)
		gameOver = true;
}