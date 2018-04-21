#pragma once
#include "IComponent.h"
#include "IUpdateableComponent.h"
#include "IMessageableComponent.h"

#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "InputHandlerToGameObjectMessage.h"
#include "SpriteAnimatedComponent.h" //added so that we can change the sprite animation when turning left, etc but doesn't work yet. 
#include "CollisionMessage.h"

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

	bool _canGoTop;
	bool _canGoBot;
	bool _canGoLeft;
	bool _canGoRight;
	
};

