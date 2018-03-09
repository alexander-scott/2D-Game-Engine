#pragma once

#include "PolygonColliderComponent.h"

class BoxColliderComponent : public PolygonColliderComponent
{
public:
	BoxColliderComponent(TransformComponent* trans, RigidBodyComponent* rb);
	~BoxColliderComponent();

	void SetBox(float hw, float hh);
};

