#pragma once

#include "IComponent.h"
#include "IMessageableComponent.h"
#include "IUpdateableComponent.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "AudioSourceComponent.h"

class AControllerComponent : public IComponent, public IMessageableComponent, public IUpdateableComponent
{
public:
	AControllerComponent();
	~AControllerComponent();

	void SetDependencies(TransformComponent* transform, RigidBodyComponent* rigidbody, AudioSourceComponent* audioSource)
	{
		_transform = transform; _rigidbody = rigidbody; _audioSource = audioSource;
	}

	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IComponentMessage& message) override;

	TransformComponent* GetTransform() { return _transform; }
	RigidBodyComponent* GetRigidbody() { return _rigidbody; }

private:
	void ProcessCommand(InputGenericStateMessageType type, sCommand command, float range);

	TransformComponent *			_transform;
	RigidBodyComponent*				_rigidbody;
	AudioSourceComponent*			_audioSource;

	bool _leftPressed, _rightPressed, _upPressed, _downPressed;
	float _previousBounceTimer;

	const float JUMP_VELOCITY = 200;
};

