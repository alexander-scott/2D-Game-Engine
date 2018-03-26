#pragma once

#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "TextRendererComponent.h"

#include "RigidBodyComponent.h"
#include "CircleColliderComponent.h"
#include "PolygonColliderComponent.h"
#include "BoxColliderComponent.h"

namespace ComponentFactory
{
	// Core
	TransformComponent * MakeTransformComponent(Vec2 position, float rotation, float scale);

	// Graphics
	SpriteRendererComponent * MakeSpriteRendererComponent(Vec2 position, float rotation, float scale, RECT* rect, Vec2 offset, string name);
	TextRendererComponent * MakeTextRendererComponent(Vec2 position, float rotation, float scale, RECT *rect, Vec2 offset, std::string text, float4* rgb);
	
	// Physics
	RigidBodyComponent * MakeRigidbodyComponent(float staticF, float dynamicF, float rest, float density, bool isStatic, bool lockRotation);
	CircleColliderComponent * MakeCircleColliderComponent(float radius);
	PolygonColliderComponent * MakePolygonCollider(Vec2* verticies, int vertexCount);
	BoxColliderComponent * MakeBoxCollider(float width, float height);
}