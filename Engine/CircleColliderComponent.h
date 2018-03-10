#pragma once

#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"

class CircleColliderComponent : public ColliderComponent
{
public:
	CircleColliderComponent(TransformComponent* trans, RigidBodyComponent* rb);
	~CircleColliderComponent();

	void SetRadius(float rad) { _radius = rad; }
	float GetRadius() { return _radius; }

	virtual ColliderType GetType(void) const override { return ColliderType::eCircle; }
	virtual void ComputeMass(float density) override;
	virtual Rect GetRect() override;

	virtual Vec2 GetCentre() override { return Vec2(_transformComponent->GetWorldPosition().x + (_radius/2), _transformComponent->GetWorldPosition().y + (_radius / 2)); }

private:
	float		_radius;
};

