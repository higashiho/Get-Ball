#include "Game.h"
#include "SelectScene.h"



// �E�C���h�E�̃T�C�Y
const int SIZE_X = 1000, SIZE_Y = 750;
//���\���̈��y���W
const int BORDER_Y = 70;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;
	if (game.Initialize())
	{
		//�ȉ�����������====================================

		ClearDrawScreen();
		game.GetInput()->InitializationMaus();

		// �ȏ㏉��������===================================

		// �ȉ�������\�������ݒ�===========================

		//�����̑傫��
		SetFontSize(50);
		//�����̃t�H���g
		ChangeFont("Impact");
		//�����\���ݒ�
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);

		// �ȏ㕶����\���ݒ�===============================


		// �ȉ��Q�[�����C�����[�v===========================

		while (!ProcessMessage())
		{
			game.GetSelectScene()->SceneMove(&game);
			// sceneFlag��End�̏�ԂŔ����Ă�����Q�[���I��
			if (game.GetSelectScene()->GetSceneFlag() == END)
				break;
		}

		// �ȏチ�C�����[�v=================================
	}

	// �ȉ��Q�[���I����̏���===============================

	ClearDrawScreen();
	unsigned int Cr;
	Cr = GetColor(255, 255, 255);	//����ݒ�
	DrawString(250, 240 - 32, "Thank you for Playing", Cr);
	game.Shutdown();	// �摜�폜�֐�

	// �ȏ�Q�[���I����̏���===============================

	return 0;
}