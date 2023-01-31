#include "SelectScene.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "EndScene.h"

SelectScene::~SelectScene()
{
	SAFE_DELETE(pScene);
}


// ���Z�b�g�֐�
void SelectScene::ResetVariable(Game* game)
{
	// ���̎��Ԃ�ݒ�
	game->SetStartTime(GetNowCount());
	// �J�E���g������
	game->SetCount(START_COUNT);
	// �Q�[���I�[�o�[�t���O������
	game->SetGameOverFlag(false);


	// �^�C�g���̔w�i�������ĐV�������C���p�̃f�[�^��ǂݍ���
	game->UnloadData();
	game->LoadData(eGamePhase);

}

// �V�[������
void SelectScene::SceneMove(Game* game)
{
	GameSceneResultCode rc = GAMESCENE_DEFAULT;

	switch (eGamePhase) {
	case GAMEPHASE_INIT:
		eGamePhase = GAMEPHASE_RESET;

	// �������Z�b�g
	case GAMEPHASE_RESET:
		SAFE_DELETE(pScene);
		pScene = new TitleScene();
		eGamePhase = GAMEPHASE_TITLE;
		ResetVariable(game);
		game->LoadData(eGamePhase);

	// �^�C�g���V�[��
	case GAMEPHASE_TITLE:
		if (pScene != NULL)
			rc = pScene->Move(game);
		if (rc == GAMESCENE_DEFAULT)
			break;

		SAFE_DELETE(pScene);
		pScene = new MainScene();
		eGamePhase = GAMEPHASE_GAME;
		game->LoadData(eGamePhase);

	// �C���Q�[��
	case GAMEPHASE_GAME:
		if (pScene != NULL)
			rc = pScene->Move(game);
		if (rc == GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(pScene);
		pScene = new EndScene();
		eGamePhase = GAMEPHASE_GAMEOVER;
		game->LoadData(eGamePhase);

	// ���U���g�V�[��
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
