#pragma once

#include "ColliderComponent.h"

class PolygonColliderComponent : public ColliderComponent
{
public:
	PolygonColliderComponent(string componentType = "PolygonColliderComponent");
	~PolygonColliderComponent();

	virtual void Start() override;

	virtual ColliderType GetType(void) const override { return ColliderType::ePolygon; }
	virtual void ComputeMass(float density) override;
	virtual Rect GetRect() override;

	virtual Vec2 GetCentre() override { return Vec2(_transformComponent->GetWorldPosition().x + _halfWidth, _transformComponent->GetWorldPosition().y + _halfHeight); }

	void SetVerticies(Vec2 *vertices, int count);
	Vec2 GetSupport(const Vec2& dir);

	int VertexCount;
	Vec2 Vertices[MAX_POLY_VERTEX_COUNT];
	Vec2 Normals[MAX_POLY_VERTEX_COUNT];

protected:	
	float				_halfWidth;
	float				_halfHeight;

private:
	Vec2				_centre;
};

