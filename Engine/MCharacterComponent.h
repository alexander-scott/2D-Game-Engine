#pragma once
#include "IComponent.h"
#include "IUpdateableComponent.h"
#include "RigidBodyComponent.h"
#include "IMessageableComponent.h"
#include "TransformComponent.h"

class MCharacterComponent : public IComponent, public IUpdateableComponent, public IMessageableComponent
{
public:
	MCharacterComponent();
	~MCharacterComponent();

	virtual void Update(float deltaTime) override;
	virtual void RecieveMessage(IComponentMessage& msg) override;

	void SetDependencies(TransformComponent* transformComponent, RigidBodyComponent* rigidBodyComponent) {
		_transformComponent = transformComponent;
		_rigidBodyComponent = rigidBodyComponent;
	}


private :
	TransformComponent * _transformComponent;
	RigidBodyComponent * _rigidBodyComponent;
};

