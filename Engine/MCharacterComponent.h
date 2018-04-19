#pragma once
#include "IComponent.h"
#include "IUpdateableComponent.h"
#include "RigidBodyComponent.h"
#include "IMessageableComponent.h"
#include "TransformComponent.h"
#include "InputHandlerToGameObjectMessage.h"
#include "SpriteAnimatedComponent.h"

class MCharacterComponent : public IComponent, public IUpdateableComponent, public IMessageableComponent
{
public:
	MCharacterComponent();
	~MCharacterComponent();

	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IComponentMessage& msg) override;

	void SetDependencies(TransformComponent* transformComponent, RigidBodyComponent* rigidBodyComponent, SpriteAnimatedComponent* spriteAnimatedComponent) {
		_transformComponent = transformComponent;
		_rigidBodyComponent = rigidBodyComponent;
		_spriteAnimatedComponent = spriteAnimatedComponent;
	}


	void ProcessInput(InputGenericStateMessageType msgType, sCommand msgCommand, float msgRange);

private :
	TransformComponent * _transformComponent;
	RigidBodyComponent * _rigidBodyComponent;
	SpriteAnimatedComponent *_spriteAnimatedComponent;

	bool _goesTop;
	bool _goesBot;
	bool _goesLeft;
	bool _goesRight;

};

