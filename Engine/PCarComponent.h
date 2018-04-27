#pragma once
#include "IComponent.h"
#include "IMessageableComponent.h"
#include "IUpdateableComponent.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"

class PCarComponent : public IComponent, public IMessageableComponent, public IUpdateableComponent
{
public:
	PCarComponent();
	~PCarComponent();

	void SetDependencies(TransformComponent* transform, RigidBodyComponent* rigidbody)
	{
		_transform = transform; _rigidbody = rigidbody;
	}

	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IComponentMessage& message) override;
private:
	void ProcessCommandTrigger(InputGenericStateMessageType type, sCommand command, float range);
	void ProcessCommandStick(InputGenericStateMessageType type, sCommand command, float range);
	void ProcessCommandButton(InputGenericStateMessageType type, sCommand command, float range);

	TransformComponent * _transform;
	RigidBodyComponent* _rigidbody;

	//buttons
	bool _leftPressed, _rightPressed, _throttlePressed, _brakePressed;
	//sticks and triggers
	float _leftStickAnalog, _throttleAnalog, _brakeAnalog;
};

