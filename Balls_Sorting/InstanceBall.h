#pragma once
#include "Game.h"
#include "Actor.h"
class InstanceBall
{
public:
	void Instance(class Game*);
	InstanceBall();

private:
	// �C���X�^���X����p�^�C�}�[
	int instanceTimer;			
};

