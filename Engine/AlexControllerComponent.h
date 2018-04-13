#pragma once

#include "IComponent.h"
#include "IMessageableComponent.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"

class AlexControllerComponent : public IComponent, public IMessageableComponent
{
public:
	AlexControllerComponent();
	~AlexControllerComponent();

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

