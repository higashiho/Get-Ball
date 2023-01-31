
#pragma once
class Component
{
public:
	// Constructor
	// (the lower the update order, the earlier the component updates)
	Component(class Actor* owner, int updateOrder = 100);
	// Destructor
	virtual ~Component();
	// Update this component by delta time
	virtual void Update(float deltaTime);

	int GetUpdateOrder() const { return updateOrder; }
protected:
	// Owning actor
	class Actor* owner;
	// Update order of component
	int updateOrder;
};
