#pragma once
#include "IComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"


class MBackgroundComponent : public IComponent
{
public:
	MBackgroundComponent();
	~MBackgroundComponent();


	void SetDependencies(TransformComponent* transformComponent, RigidBodyComponent* rigidBodyComponent) {
		_transformComponent = transformComponent;
		_rigidBodyComponent = rigidBodyComponent;
	}

private:
	TransformComponent * _transformComponent;
	RigidBodyComponent * _rigidBodyComponent;
};

