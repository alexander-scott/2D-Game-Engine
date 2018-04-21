#pragma once
#include "IUpdateableComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "SpriteAnimatedComponent.h"

class MChestComponent : public IComponent, IUpdateableComponent
{
public:
	MChestComponent();
	~MChestComponent();

	void SetDependencies(TransformComponent* transformComponent, RigidBodyComponent* rigidBodyComponent, SpriteAnimatedComponent* spriteAnimatedComponent) {
		_transformComponent = transformComponent;
		_rigidBodyComponent = rigidBodyComponent;
		_spriteAnimatedComponent = spriteAnimatedComponent;
	}
	void Update(float deltaTime) override;

private:
	TransformComponent * _transformComponent;
	RigidBodyComponent * _rigidBodyComponent;
	SpriteAnimatedComponent *_spriteAnimatedComponent;
};

