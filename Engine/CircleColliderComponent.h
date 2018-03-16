#pragma once

#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"

class CircleColliderComponent : public ColliderComponent
{
public:
	CircleColliderComponent();

	void SetRadius(float rad) { _baseRadius = rad; }
	float GetRadius() { return _baseRadius; }

	virtual void Start() override;
	virtual void ComputeMass(float density) override;
	virtual ColliderType GetType(void) const override { return ColliderType::eCircle; }	
	virtual Rect GetRect() override;
	virtual Vec2 GetCentre() override { return Vec2(_transformComponent->GetWorldPosition().x + (_radius/2), _transformComponent->GetWorldPosition().y + (_radius / 2)); }

private:
	float		_baseRadius;
	float		_radius;
};

