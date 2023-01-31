#pragma once
#include "Game.h"
#include "IGameScene.h"
class TitleScene :
    public IGameScene
{
public:
    TitleScene();
    virtual ~TitleScene();
    virtual GameSceneResultCode Move(class Game* game) override;
private:

    //‰æ–Ê‚Ì’†S
    int centerX, centerY;
};

