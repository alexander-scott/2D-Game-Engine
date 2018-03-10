#pragma once

#include "PolygonColliderComponent.h"

class BoxColliderComponent : public PolygonColliderComponent
{
public:
	BoxColliderComponent(TransformComponent* trans, RigidBodyComponent* rb, float width, float height);
	~BoxColliderComponent();

	float GetWidth() { return _width; }
	float GetHeight() { return _height; }

private:
	void SetBox(float hw, float hh);

	float		_height;
	float		_width;
};

