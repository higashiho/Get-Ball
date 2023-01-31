#pragma once
#include "IGameScene.h"
class EndScene :
    public IGameScene
{
public:
	EndScene();

    virtual ~EndScene();
    virtual GameSceneResultCode Move(class Game* game) override;
    
private:

    //��ʂ̒��S
    int centerX, centerY;
};

