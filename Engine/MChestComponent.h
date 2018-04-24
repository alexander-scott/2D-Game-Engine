#pragma once
#include "IComponent.h"
#include "IUpdateableComponent.h"
#include "IMessageableComponent.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "SpriteAnimatedComponent.h"

#include "CollisionMessage.h"
#include "InputHandlerToGameObjectMessage.h"


class MChestComponent : public IComponent, public IUpdateableComponent, public IMessageableComponent
{
public:
	MChestComponent();
	~MChestComponent();
			
	void SetDependencies(TransformComponent* transformComponent, RigidBodyComponent* rigidBodyComponent, SpriteAnimatedComponent* spriteAnimatedComponent) {
		_transformComponent = transformComponent;
		_rigidBodyComponent = rigidBodyComponent;
		_spriteAnimatedComponent = spriteAnimatedComponent;
	}

	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IComponentMessage & msg) override;

private:
	TransformComponent * _transformComponent;
	RigidBodyComponent * _rigidBodyComponent;
	SpriteAnimatedComponent *_spriteAnimatedComponent;
};

