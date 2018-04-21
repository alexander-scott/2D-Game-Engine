#pragma once
#include "ICommand.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "SpriteAnimatedComponent.h"

#include "IUpdateableComponent.h"

class MPhantomComponent : public IComponent, public IUpdateableComponent 
{
public:
	MPhantomComponent();
	~MPhantomComponent();
	void SetDependencies(TransformComponent* transformComponent, RigidBodyComponent* rigidBodyComponent, SpriteAnimatedComponent* spriteAnimatedComponent) {
		_transformComponent = transformComponent;
		_rigidBodyComponent = rigidBodyComponent;
		_spriteAnimatedComponent = spriteAnimatedComponent;
	}
	void Update(float deltaTime) override;

private :
	TransformComponent * _transformComponent;
	RigidBodyComponent * _rigidBodyComponent;
	SpriteAnimatedComponent *_spriteAnimatedComponent;
};

