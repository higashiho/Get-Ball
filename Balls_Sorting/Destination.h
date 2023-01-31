#pragma once
#include "Actor.h"
#include "Game.h"
class Destination :
    public Actor
{
public:
    Destination(class Game*, Vector2, int);
    void UpdateActor(float deltaTime) override;
    void Collision(int patternBall);
    ~Destination();
    // 以下取得用================================

    int GetGoalNumber() { return goalNumber; }

    // 以上取得用================================
private:
    // 衝突矩形へのポインタ
    class BoxComponent* boxCol;
    // 自身のゴール判断用(0の場合はレッドボールのゴール、１の場合はイエローボールのゴール）
    int goalNumber;
};

