
#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owners, int drawOrder)
	:SpriteComponent(owners, drawOrder)
	, currFrame(0.0f)
	, animFPS(5.0f)// flame rate
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (animTextures.size() > 0)
	{
		// Update the current frame based on frame rate
		// and delta time
		currFrame += animFPS * deltaTime;
		
		// Wrap current frame if needed
		while (currFrame >= animTextures.size())
		{
			currFrame -= animTextures.size();
		}

		// Set the current texture
		SetTexture(animTextures[static_cast<int>(currFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(std::vector<int> textures)
{
	// handle‚Ìvector ”z—ñ
	animTextures = textures;
	if (animTextures.size() > 0)
	{
		// Set the active texture to first frame
		currFrame = 0.0f;
		SetTexture(animTextures[0]);
	}
}
