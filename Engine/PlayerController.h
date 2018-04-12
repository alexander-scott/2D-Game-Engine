#pragma once

#include "IComponent.h"
#include "IMessageableComponent.h"

#include "TransformComponent.h"

class PlayerController : public IComponent, public IMessageableComponent
{
public:
	PlayerController();
	~PlayerController();

	void SetDependencies(TransformComponent* transform) { _transform = transform; }

	virtual void RecieveMessage(IComponentMessage& message) override;

private:
	TransformComponent * _transform;
};

