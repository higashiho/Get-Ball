
#pragma once
#include "Component.h"

class SpriteComponent : public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw();
	virtual void SetTexture(int texture);

	inline int GetDrawOrder() const { return drawOrder; }
	inline int GetTexHeight() const { return texHeight; }
	inline int GetTexWidth() const { return texWidth; }
protected:
	int texture;		// handle
	int drawOrder;
	int texWidth;
	int texHeight;
};
