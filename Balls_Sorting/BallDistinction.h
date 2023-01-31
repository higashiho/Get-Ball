#pragma once
#include "BasicBall.h"
#include <math.h>
#include "Actor.h"
class BallDistinction :
	public BasicBall
{
public:
	BallDistinction(class Game* game, int bowlsNumber);
	~BallDistinction();
	void UpdateActor(float deltaTime) override;

	void Update(float deltaTime) override;

	void Collision() override;
	void Reset() override;
	Vector2 Movement(Vector2, float) override;

private:


};