#pragma once
#include "IComponent.h"
#include "IUpdateableComponent.h"


#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"

class MBackgroundComponent : public IComponent, public IUpdateableComponent
{
public:
	MBackgroundComponent();
	~MBackgroundComponent();


	virtual void Update(float deltaTime) override;

	void SetDependencies(TransformComponent* transformComponent, RigidBodyComponent* rigidBodyComponent, BoxColliderComponent *boxColliderComponent) {
		_transformComponent = transformComponent;
		_rigidBodyComponent = rigidBodyComponent;
		_boxColliderComponent = boxColliderComponent;
	}


private:
	TransformComponent * _transformComponent;
	RigidBodyComponent * _rigidBodyComponent;
	BoxColliderComponent *_boxColliderComponent;
};

