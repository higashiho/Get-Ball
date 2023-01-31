#pragma once
#include "IGameScene.h"
enum GamePhase {
	GAMEPHASE_INIT = 0,
	GAMEPHASE_RESET = 1,
	GAMEPHASE_TITLE = 0x010,
	GAMEPHASE_GAME = 0x100,
	GAMEPHASE_GAMEOVER = 0x200,
	GAMEPHASE_END = 0x300
};

enum GameSceneResultCode {
	GAMESCENE_DEFAULT = 0,
	GAMESCENE_END_OK = 1,
	GAMESCENE_END_TIMEOUT = 2,
	GAMESCENE_END_FAILURE = 3
};

class SelectScene 
{
public:
	~SelectScene();
	void ResetVariable(class Game* game);

	void SceneMove(class Game* game);

	// �ȉ�����p===================================
	void SetSceneFlag(GamePhase value) { eGamePhase = value; }
	// �ȏ����p===================================
	
	// �ȉ��擾�p===================================
	GamePhase GetSceneFlag() { return eGamePhase; }
	// �ȏ�擾�p===================================
private:
	// �X�s�[�h
	int SpeedX, SpeedY;
	// �A�Ŗh�~�p
	bool one;

	class IGameScene* pScene;		//	�V�[��
	GamePhase	eGamePhase;	//	��ԕϐ�
};

