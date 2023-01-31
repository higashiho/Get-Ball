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
    // �ȉ��擾�p================================

    int GetGoalNumber() { return goalNumber; }

    // �ȏ�擾�p================================
private:
    // �Փˋ�`�ւ̃|�C���^
    class BoxComponent* boxCol;
    // ���g�̃S�[�����f�p(0�̏ꍇ�̓��b�h�{�[���̃S�[���A�P�̏ꍇ�̓C�G���[�{�[���̃S�[���j
    int goalNumber;
};

