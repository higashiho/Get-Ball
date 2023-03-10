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

    //画面の中心
    int centerX, centerY;
};

