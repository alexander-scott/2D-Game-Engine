#pragma once

#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "TextRendererComponent.h"
#include "SpriteAnimatedComponent.h"

#include "RigidBodyComponent.h"
#include "CircleColliderComponent.h"
#include "PolygonColliderComponent.h"
#include "BoxColliderComponent.h"

namespace ComponentFactory
{
	// Core
	TransformComponent * MakeTransformComponent(Vec2 position, float rotation, float scale);
	SpriteRendererComponent * MakeSpriteRendererComponent(RECT* rect, Vec2 offset, string text, string name, string animation);
	TextRendererComponent * MakeTextRendererComponent(RECT * rect, Vec2 offset, std::string text, float4 * rgb3);
	SpriteAnimatedComponent * MakeSpriteAnimatedComponent(RECT* rect, Vec2 offset, string text, string name, string animation);

	// Physics
	RigidBodyComponent * MakeRigidbodyComponent(float staticF, float dynamicF, float rest, float density, bool isStatic, bool lockRotation, bool isKinematic);
	CircleColliderComponent * MakeCircleColliderComponent(float radius);
	PolygonColliderComponent * MakePolygonCollider(Vec2* verticies, int vertexCount);
	BoxColliderComponent * MakeBoxCollider(float width, float height);
}