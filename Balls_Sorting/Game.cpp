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

// Game�N���X�̃��\�b�h�̒�`(���������\�b�h)
bool Game::Initialize()
{
	if (DxLib_Init() == -1)				// �c�w���C�u��������������
	{
		return false;					// �G���[���N�����璼���ɏI��
	}
	SetGraphMode(SIZE_X, SIZE_Y, 32);		// ��ʂ̑傫����SizeX �~ SizeY �ɐݒ肷��
	ChangeWindowMode(TRUE);				// �E�C���h�E���[�h

	ticksCount = GetNowCount();

	return true;
}

// �Q�[���̃��C�����[�v���\�b�h
void Game::RunLoop()
{
	while (!gameOver)
	{
		// �^�C�}�[
		DisplayTime();
		// ���̓��\�b�h
		processInput();
		// �Q�[���X�V���\�b�h
		UpdateGame();
		// �摜�̕\�����\�b�h
		GenerateOutput();
		// �J�E���g��0�ɂȂ����烋�[�v�I�����\�b�h
		JudgCount();
		// �^�u�L�[���������烊�U���g�ֈړ�
		if (CheckHitKey(KEY_INPUT_TAB)) { break; }
#ifdef _DEBUG
		// �G�X�P�[�v�L�[�������ƃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE)) { break; }
#endif
	}
}

// ���͂̃��\�b�h�̒�`
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
			// �Q�[���X�^�[�g����̎���
			time = GetNowCount() - startTime;
			//�c�莞�Ԃ̌v�Z
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

// �Q�[���̍X�V���\�b�h�̒�`
void Game::UpdateGame()
{
	// �ҋ@����(16ms�j�ݒ�
	WaitTimer(WAIT_TIME);
	// �P���[�v���Ԃ̌v�Z
	float deltaTime = (GetNowCount() - ticksCount) / ADJUST_TIMER;
	if (deltaTime > MAX_DELTA_TIME)
	{
		deltaTime = MAX_DELTA_TIME;
	}
	ticksCount = GetNowCount();

	//�V�[���ɓo�ꂷ��I�u�W�F�N�g(Actor�N���X���p��)���X�V
	updatingActors = true;
	for (auto actor : actors)
	{
		actor->Update(deltaTime);
	}

	// �V�[���ɓo�ꂷ��I�u�W�F�N�g��ǉ�����ꍇ�̃��[�v
	for (auto pending : pendingActors)
	{
		// vector�^�z��̍X�V���\�b�h
		actors.emplace_back(pending);		
	}
	// vector�^�z����N���A(�S����)���\�b�h
	pendingActors.clear();					

	// ���񂾃A�N�^�[���e���|�����x�N�^�[�ɒǉ�
	// vector�^�z��(Actor�N���X�̃|�C���^�[�����߂�z��)
	std::vector<Actor*> deadActors;					
	for (auto actor : actors)
	{
		// Actor�N���X�̃I�u�W�F�N�g�̏�Ԃ�EDead�̏ꍇ
		if (actor->GetState() == Actor::EDead)		
		{
			// vector�^�z��̍X�V���\�b�h
			deadActors.emplace_back(actor);			
		}
	}

	// Actor�N���X�̃I�u�W�F�N�g�̏��EDead�̂��ׂĂ�����
	for (auto actor : deadActors)
	{
		//�v�f���ׂĂ�����(��ector�^�z���������)
		delete actor;			
	}

}

// �V�[���̑S�̂�`�悷�郁�\�b�h
void Game::GenerateOutput()
{
	// ��ʃN���A
	ClearDrawScreen();						
	// Box��ʃN���A
	DrawBox(0, 0, SIZE_X, SIZE_Y, GetColor(0, 0, 0), 1);

	// ���ׂẴX�v���C�g�ɂ��ĕ`�揇���l�����ĕ`��
	for (auto sprite : sprites)
	{
		// �w�i���܂߂ĉ摜��`�悷�郁�\�b�h
		sprite->Draw();					
	}

}

// �V�[���摜�f�[�^��ǂݍ��ރ��\�b�h�̒�`
void Game::LoadData(const int noeScene)
{

	Vector2 pos, pos2;
	pos.x = ADJUSMENT_POS_X, pos.y = centerY - BORDER_Y;
	pos2.x = SIZE_X - ADJUSMENT_POS_X, pos2.y = centerY - BORDER_Y;
	BallPattern pBalls;
	switch (noeScene)
	{
		// �^�C�g���ł̃f�[�^
	case TITEL_SCENE:
		BackgroundLoading("image/Title.jpg", "image/Title_flip.jpg", SCROLL_LOW_SPEED);
		BackgroundLoading("image/Dot.png", "image/Dot.png", SCROLL_HIGH_SPEED);
		break;
		// ���C���V�[���ł̃f�[�^
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

// �w�i�̓ǂݍ��݃��\�b�h
void Game::BackgroundLoading(std::string str,std::string str2 ,float speed)
{
	// �w�i�p�̃A�N�^���쐬����
	Actor* temp = new Actor(this);
	// ���S�ɕ\���Ay���W�͉��Ƀe�L�X�g�����邽�ߏ�����ɐݒ�
	temp->SetPosition(Vector2(500.0f, 325.0f));

	// �w�i�̃X�v���C�g���쐬
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 50);
	// �w�i�̑傫��
	bg->SetScreenSize(Vector2(SIZE_X, SIZE_Y));
	std::vector<int> bgtexs = {
		// �w�i�摜�̃n���h��(�����^)��o�^
		GetTexture(str),
		GetTexture(str2),
	};

	// mBGTexures �o�^(�n���h���̔z����X�v���C�g�ɓo�^)
	bg->SetBGTextures(bgtexs);
	// �X�v���C�g�̃X�N���[���X�s�[�h�̐ݒ�
	bg->SetScrollSpeed(-speed);

}
// �Q�[���I�����̉摜�f�[�^�̏������\�b�h
void Game::UnloadData()
{
	// �Q�[���ɓo�^����Ă���Actor���S�ď�������܂Ń��[�v�𑱂���
	while (!actors.empty())
	{
		// �Q�[���ɓo�^����Ă���Actor�̍Ō�������ď�������
		delete actors.back();			
	}
	// �w�i�摜�̃f�[�^������
	textures.clear();					
}

// �摜�f�[�^�����ۂɓǂݍ���ł��̃n���h��(����)��Ԃ����\�b�h
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
		// �摜�̃n���h����Ԃ�
		tex = LoadGraph(fileName.c_str());
		if (tex == -1)
		{
			std::cout << "Failed to load texture file " << fileName << "\n";
			return -1;
		}
		// map�^�z����X�V(�z��ɂQ�̒l���Z�b�g�œo�^)
		textures.emplace(fileName.c_str(), tex);			
	}
	// handle��Ԃ�
	return tex;				
}

// �Q�[���̏I�����\�b�h�̒�`
void Game::Shutdown()
{
	// �V�[����Actor����щ摜�f�[�^�̏���(����j
	UnloadData();			

	WaitKey();          //�L�[�̓��͑҂�
	// �c�w���C�u�����g�p�̏I������
	DxLib_End();			

}

// �Q�[���V�[����Actor��ǉ����郁�\�b�h��`
void Game::AddActor(Actor* actor)
{
	// Actor��o�^����^�C�~���O�����Ă��邩�ǂ���
	if (updatingActors)						
	{
		// ����o�^���X�g�ɒǉ�
		pendingActors.emplace_back(actor);		
	}
	else
	{
		// �V�[���ɓo�^
		actors.emplace_back(actor);			
	}
}

// �Q�[���V�[���ɂ���Actor���폜���郁�\�b�h��`
void Game::RemoveActor(Actor* actor)
{
	// �ҋ@���X�g�ɂ��邩�ǂ������������Č�����Ώ���
	auto iter = std::find(pendingActors.begin(), pendingActors.end(), actor);
	if (iter != pendingActors.end())
	{

		std::iter_swap(iter, pendingActors.end() - 1);
		pendingActors.pop_back();
	}

	// �V�[���ɂ���ꍇ�Ɍ�����Ώ���
	iter = std::find(actors.begin(), actors.end(), actor);
	if (iter != actors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, actors.end() - 1);
		actors.pop_back();
	}
}

// �X�v���C�g��ǉ����郁�\�b�h
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
		// �X�v���C�g�̕`�揇�����߂�
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	// Inserts element before position of iterator
	sprites.insert(iter, sprite);
}
//�X�v���C�g�̏������\�b�h�̒�`
void Game::RemoveSprite(SpriteComponent* sprite)
{
	// �X�v���C�g��T��
	auto iter = std::find(sprites.begin(), sprites.end(), sprite);
	// �X�v���C�g�̏���
	sprites.erase(iter);
}

// �{�[���̐������\�b�h�̒�`
void Game::AddSortingBowls(BallDistinction* other)
{
	ballDistinctions.emplace_back(other);
}

// �{�[���̏������\�b�h�̒�`
void Game::RemoveSortingBowls(BallDistinction* other)
{
	auto iter = std::find(ballDistinctions.begin(),
		ballDistinctions.end(), other);
	if (iter != ballDistinctions.end())
	{
		ballDistinctions.erase(iter);
	}
}

//�Q�[�����Ԃƃ{�[���̏�����������\������֐�
void Game::DisplayTime() {		
	// �Q�[���X�^�[�g����̎���
	time = GetNowCount() - startTime;
	//�c�莞�Ԃ̌v�Z
	int dis = playTime * ADJUST_TIMER + time;

	//�\���̈���w��F�ŃN���A����
	DrawBox(1, SIZE_Y - BORDER_Y + 1, SIZE_X, SIZE_Y, GetColor(0, 255, 0), 1);
	DrawFormatString(centerX + 200, SIZE_Y - BORDER_Y + 2, GetColor(255, 255, 255), "Time=%d", dis / ADJUST_TIMER);
	DrawFormatString(0, SIZE_Y - BORDER_Y + 2, GetColor(255, 255, 255), "Count=%d", count);
}

// �{�[���������ꂽ�ꍇ��莞�Ԍ�Ƀt���O��on�ɂ���֐�
bool Game::waitInstans(bool* flag, int* timer)
{
	if (flag == nullptr || timer ==  nullptr)
		throw std::exception("error!");

	if (!*flag)
	{
		*timer -= TIMER_COUNT;
		// flag���܂�Ă����Ԃł�timer���O�̏ꍇ�̂�true��ς���
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

// count���O�ɂȂ�����Q�[�����[�v���甲���o������
void Game::JudgCount()
{
	if (count <= 0)
		gameOver = true;
}