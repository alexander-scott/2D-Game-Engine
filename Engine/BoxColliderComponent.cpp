#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent(TransformComponent* trans, RigidBodyComponent* rb) 
	: PolygonColliderComponent(trans, rb)
{
}

BoxColliderComponent::~BoxColliderComponent()
{
}

void BoxColliderComponent::SetBox(float hw, float hh)
{
	_halfWidth = hw; _halfHeight = hh;

	VertexCount = 4;
	Vertices[0].Set(-hw, -hh);
	Vertices[1].Set(hw, -hh);
	Vertices[2].Set(hw, hh);
	Vertices[3].Set(-hw, hh);
	Normals[0].Set(0.0f, -1.0f);
	Normals[1].Set(1.0f, 0.0f);
	Normals[2].Set(0.0f, 1.0f);
	Normals[3].Set(-1.0f, 0.0f);
}
