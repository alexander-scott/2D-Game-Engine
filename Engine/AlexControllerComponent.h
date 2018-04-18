#pragma once

#include "IComponent.h"
#include "IMessageableComponent.h"
#include "IUpdateableComponent.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"

class AlexControllerComponent : public IComponent, public IMessageableComponent, public IUpdateableComponent
{
public:
	AlexControllerComponent();
	~AlexControllerComponent();

	void SetDependencies(TransformComponent* transform, RigidBodyComponent* rigidbody) 
	{
		_transform = transform; _rigidbody = rigidbody;
	}

	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IComponentMessage& message) override;

private:
	void ProcessCommand(InputGenericStateMessageType type, sCommand command, float range);

	TransformComponent * _transform;
	RigidBodyComponent* _rigidbody;

	bool _leftPressed, _rightPressed, _upPressed, _downPressed;
	float _previousBounceTimer;

	const float JUMP_VELOCITY = 200;
};

