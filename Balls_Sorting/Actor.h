#pragma once
#include <vector>
#include "Math.h"
class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// Getters/setters
	inline const Vector2& GetPosition() const { return position; }
	void SetPosition(const Vector2& pos) { position = pos; }
	inline float GetScale() const { return scale; }
	void SetScale(float scales) { scale = scales; }
	inline float GetRotation() const { return rotation; }
	void SetRotation(float rota) { rotation = rota; }


	inline State GetState() const { return state; }
	void SetState(State states) { state = states; }

	inline class Game* GetGame() { return game; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	// collision radius set get
	inline float GetcRaius() const { return radius; }
	inline void  SetcRadius(float r) { radius = r; }


	Vector2  GetBsize() { return bsize; }			// 衝突矩形のサイズを返すメソッド
	void  SetBsize(Vector2 size) { bsize = size; }// 衝突矩形のサイズを設定するメソッド

	void RemoveActor();
private:
	// Actor's state
	State state;

	// Transform
	Vector2 position;
	float scale;
	float rotation;

	std::vector<class Component*> components;
	class Game* game;
	// collision Radius;
	float radius;
	Vector2 bsize;
};