#pragma once

#include "TransformComponent.h"

#include "RigidBodyComponent.h"
#include "CircleColliderComponent.h"
#include "PolygonColliderComponent.h"
#include "BoxColliderComponent.h"

namespace ComponentFactory
{
	// Core
	TransformComponent * MakeTransformComponent(Vec2 position, float rotation, float scale);

	// Physics
	RigidBodyComponent * MakeRigidbodyComponent(float staticF, float dynamicF, float rest, float density, bool isStatic, bool lockRotation);
	CircleColliderComponent * MakeCircleColliderComponent(float radius);
	PolygonColliderComponent * MakePolygonCollider(Vec2* verticies, int vertexCount);
	BoxColliderComponent * MakeBoxCollider(float width, float height);
}