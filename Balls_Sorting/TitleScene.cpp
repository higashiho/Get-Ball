#include "TitleScene.h"
TitleScene::TitleScene()
{
	centerX = SIZE_X / 2; centerY = SIZE_X / 2;

}
TitleScene::~TitleScene()
{

}

// �^�C�g���V�[���p�֐�
GameSceneResultCode TitleScene::Move(Game* game)
{
	unsigned int collar;
	collar = GetColor(255, 255, 255);	//����ݒ�

	// �^�C�g���V�[���ł̃��[�v
	while (true)
	{
		// �Q�[���X�V���\�b�h
		game->UpdateGame();
		// �摜�̕\�����\�b�h
		game->GenerateOutput();
		// �^�C�g���摜�\��
		LoadGraphScreen(centerX / 2, 0, "image/TitleText.png", TRUE);
		DrawBox(1, SIZE_Y - BORDER_Y + 1, SIZE_X, SIZE_Y, GetColor(255, 0, 0), 1);
		DrawString(centerX, SIZE_Y - BORDER_Y, "Please Push SPACE Key", collar);
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			ClearDrawScreen();
			return GAMESCENE_END_OK;
		}
		// �G�X�P�[�v�L�[�Ń��[�v�𔲂���
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			game->GetSelectScene()->SetSceneFlag(GAMEPHASE_END);
			break;
		}
	}
	return GAMESCENE_DEFAULT;
}
