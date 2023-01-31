

#pragma once
#include "SpriteComponent.h"
#include <vector>
//#include <unordered_map>
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	// Update animation every frame (overridden from component)
	void Update(float deltaTime) override;
	// Set the textures used for animation
	void SetAnimTextures(const std::vector<int> textures);
	// Set/get the animation FPS
	float GetAnimFPS() const { return animFPS; }
	void SetAnimFPS(float fps) { animFPS = fps; }
private:
	// All textures in the animation
	std::vector<int> animTextures;
	// Current frame displayed
	float currFrame;
	// Animation frame rate
	float animFPS;
};
