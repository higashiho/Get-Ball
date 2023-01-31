#pragma once
#include "Game.h"
#include "Actor.h"
class InstanceBall
{
public:
	void Instance(class Game*);
	InstanceBall();

private:
	// インスタンスする用タイマー
	int instanceTimer;			
};

