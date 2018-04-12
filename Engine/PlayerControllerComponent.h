#pragma once

#include "IComponent.h"
#include "IMessageableComponent.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"

class PlayerControllerComponent : public IComponent, public IMessageableComponent
{
public:
	PlayerControllerComponent();
	~PlayerControllerComponent();

	void SetDependencies(TransformComponent* transform, RigidBodyComponent* rigidbody) 
	{
		_transform = transform; _rigidbody = rigidbody;
	}

	virtual void RecieveMessage(IComponentMessage& message) override;

private:
	void ProcessCommand(sCommand command, float range);

	TransformComponent * _transform;
	RigidBodyComponent* _rigidbody;
};

