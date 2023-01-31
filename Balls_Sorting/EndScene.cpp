#include "EndScene.h"
EndScene::EndScene()
{
	centerX = SIZE_X / 2; centerY = SIZE_Y / 2;
}
EndScene::~EndScene()
{

}

// �N���A�V�[��
GameSceneResultCode EndScene::Move(Game* game) {
	unsigned int collar;
	collar = GetColor(255, 255, 255);	//����ݒ�

	// �^�C�g���V�[���ł̃��[�v
	while (true)
	{
		// �Q�[���X�V���\�b�h
		game->UpdateGame();
		// �摜�̕\�����\�b�h
		game->GenerateOutput();
		DrawBox(1, SIZE_Y - BORDER_Y + 1, SIZE_X, SIZE_Y, GetColor(255, 0, 0), 1);
		DrawString(50, SIZE_Y - BORDER_Y, "Re Play = Enter", collar);
		DrawString(centerX + 50, SIZE_Y - BORDER_Y, "Game End = Escape", collar);
		if (CheckHitKey(KEY_INPUT_RETURN)) {
			ClearDrawScreen();
			// �^�C�g���̔w�i�������ĐV�������C���p�̃f�[�^��ǂݍ���
			game->UnloadData();
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
