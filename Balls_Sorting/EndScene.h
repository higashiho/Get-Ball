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

    //‰æ–Ê‚Ì’†S
    int centerX, centerY;
};

