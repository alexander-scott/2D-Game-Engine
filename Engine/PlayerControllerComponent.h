#pragma once

#include "IComponent.h"
#include "IMessageableComponent.h"

#include "TransformComponent.h"

class PlayerControllerComponent : public IComponent, public IMessageableComponent
{
public:
	PlayerControllerComponent();
	~PlayerControllerComponent();

	void SetDependencies(TransformComponent* transform) { _transform = transform; }

	virtual void RecieveMessage(IComponentMessage& message) override;

private:
	void ProcessCommand(sCommand command, float range);

	TransformComponent * _transform;
};

