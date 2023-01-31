

#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, scrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{

	SpriteComponent::Update(deltaTime);
	for (auto& bg : bgTextures)
	{
		// Update the x offset
		bg.mOffset.x += scrollSpeed * deltaTime;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		if (bg.mOffset.x < -screenSize.x)
		{
			bg.mOffset.x = (bgTextures.size() - 1) * screenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw()
{
	// Draw each background texture
	for (auto bg : bgTextures)
	{


		int x, y, w, h;

		w = static_cast<int>(screenSize.x);
		h = static_cast<int>(screenSize.y);


		x = static_cast<int>(owner->GetPosition().x - w / 2 + bg.mOffset.x);
		y = static_cast<int>(owner->GetPosition().y - h / 2 + bg.mOffset.y);

		DrawGraph(x, y, bg.mTexture, 1);


	}
}

void BGSpriteComponent::SetBGTextures(std::vector<int> textures)
{

	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		// Each texture is screen width in offset
		temp.mOffset.x = count * screenSize.x;
		temp.mOffset.y = 0;
		bgTextures.emplace_back(temp);
		count++;
	}
}
