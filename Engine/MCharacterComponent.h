#pragma once
#include "IComponent.h"
#include "IUpdateableComponent.h"
#include "IMessageableComponent.h"

#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "InputHandlerToGameObjectMessage.h"
#include "SpriteAnimatedComponent.h" 
#include "CollisionMessage.h"

class MCharacterComponent : public IComponent, public IUpdateableComponent, public IMessageableComponent
{
public:
	MCharacterComponent();
	~MCharacterComponent();

	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IComponentMessage& msg) override;

	void SetDependencies(TransformComponent* transformComponent, RigidBodyComponent* rigidBodyComponent, SpriteAnimatedComponent* spriteAnimatedComponent/*, SpriteAnimatedComponent* spriteAnimatedComponent2*/) {
		_transformComponent = transformComponent;
		_rigidBodyComponent = rigidBodyComponent;
		_spriteAnimatedComponent = spriteAnimatedComponent;

		_startPosition = _transformComponent->GetWorldPosition();
	}


	void ProcessInput(InputGenericStateMessageType msgType, sCommand msgCommand, float msgRange);

	void ResetPosition();
	void Restart();

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

	Vec2 _startPosition;

	bool _isAlive = true;
	bool _won;
	
};

