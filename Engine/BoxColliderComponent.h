#pragma once

#include "PolygonColliderComponent.h"

class BoxColliderComponent : public PolygonColliderComponent
{
public:
	BoxColliderComponent(float width, float height);
	~BoxColliderComponent();

	virtual void Start() override;

	float GetWidth() { return _width; }
	float GetHeight() { return _height; }

private:
	void SetBox(float hw, float hh);

	float		_height;
	float		_width;
};

