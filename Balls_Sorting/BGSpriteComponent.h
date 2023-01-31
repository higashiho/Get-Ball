#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"
#include "DxLib.h"
//extern	int		DrawGraph(int x, int y, int GrHandle, int TransFlag);	// ‰æ‘œ‚Ì“™”{•`‰æ
class BGSpriteComponent : public SpriteComponent
{
	struct BGTexture
	{
		int mTexture;// handle
		Vector2 mOffset;
	};
public:
	// Set draw order to default to lower (so it's in the background)
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	// Update/draw overridden from parent
	void Update(float deltaTime) override;

	void Draw() override;
	// Set the textures used for the background
	void SetBGTextures(std::vector<int> textures);
	// Get/set screen size and scroll speed
	void SetScreenSize(const Vector2& size) { screenSize = size; }
	void SetScrollSpeed(float speed) { scrollSpeed = speed; }
	float GetScrollSpeed() const { return scrollSpeed; }
private:

	std::vector<BGTexture> bgTextures;
	Vector2 screenSize;
	float scrollSpeed;
};
