#pragma once
#include "Game.h"
#include "Input.h"

// �V�[���t���O
#define TITEL_SCENE 0x010
#define MAIN_SCENE 0x100
#define RESULT_SCENE 0x200
#define END 0x300

#define __IGAMESCENE_H__

enum GameSceneResultCode;
struct ID2D1RenderTarget;


class IGameScene
{
public:
	virtual ~IGameScene() = 0;	//	�������z�f�X�g���N�^
	virtual GameSceneResultCode Move(class Game* game) = 0;
};

