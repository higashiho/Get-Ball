#include "MainScene.h"

MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}

// ���C���V�[���֐�
GameSceneResultCode MainScene::Move(Game* game)
{
	// �Q�[�����[�v
	game->RunLoop();

	ClearDrawScreen();
	// �^�C�g���̔w�i�������ĐV�������C���p�̃f�[�^��ǂݍ���
	game->UnloadData();

	// RunLoop�𔲂����烊�U���g�ɕς���
	return GAMESCENE_END_OK;
}
