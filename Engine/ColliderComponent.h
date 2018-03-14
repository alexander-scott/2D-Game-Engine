#pragma once

#include "IComponent.h"
#include "IStartableComponent.h"

#include "Consts.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"

class ColliderComponent : public IComponent, public IStartableComponent
{
public:
	ColliderComponent(std::string type) : IComponent(type) { }

	virtual void Start() override { }

	void SetDependencies(TransformComponent* transform, RigidBodyComponent* rb) { _transformComponent = transform; _rigidyBodyComponent = rb; }

	RigidBodyComponent* GetRigidbodyComponent() { return _rigidyBodyComponent; }
	TransformComponent* GetTransformComponent() { return _transformComponent; }

	virtual ColliderType GetType(void) const = 0;
	virtual void ComputeMass(float density) = 0;
	virtual Rect GetRect() = 0;

	void SetPreviousRect(Rect r) { _previousRect = r; }
	Rect GetPreviousRect() { return _previousRect; }

	virtual Vec2 GetCentre() = 0;

	int								CentreGridSquare;
	int								LeftGridSquare;
	int								RightGridSquare;
	int								BottomGridSquare;
	int								TopGridSquare;

protected:
	TransformComponent*				_transformComponent;
	RigidBodyComponent*				_rigidyBodyComponent;
	Rect							_previousRect;
};

