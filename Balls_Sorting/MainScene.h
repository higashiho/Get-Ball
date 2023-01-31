#pragma once
#include "IGameScene.h"

class MainScene :
    public IGameScene
{
public:
    MainScene();
    
    virtual ~MainScene();
    virtual GameSceneResultCode Move(class Game* game) override;
};

