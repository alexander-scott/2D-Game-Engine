#include "ComponentFactory.h"

TransformComponent * ComponentFactory::MakeTransformComponent(Vec2 position, float rotation, float scale)
{
	TransformComponent * transform = new TransformComponent(position, rotation, scale);

	return transform;
}

SpriteRendererComponent * ComponentFactory::MakeSpriteRendererComponent(RECT* rect, Vec2 offset, string text, string name)
{
	SpriteRendererComponent * sprite = new SpriteRendererComponent(rect, offset, text, name);
	return sprite;
}

TextRendererComponent * ComponentFactory::MakeTextRendererComponent(RECT * rect, Vec2 offset, std::string text, float4 * rgb3)
{
	TextRendererComponent * textComponent = new TextRendererComponent(rect, offset, text, rgb3);
	return textComponent;
}

SpriteAnimatedComponent * ComponentFactory::MakeSpriteAnimatedComponent(RECT * rect, Vec2 offset, string text, string name, string animation)
{
	SpriteAnimatedComponent * sprite = new SpriteAnimatedComponent(rect, offset, text, name, animation);
	return sprite;
}

RigidBodyComponent * ComponentFactory::MakeRigidbodyComponent(float staticF, float dynamicF, float rest, float density, bool isStatic, bool lockRotation)
{
	RigidBodyComponent * rigidBody = new RigidBodyComponent(staticF, dynamicF, rest, density);
	if (isStatic)
		rigidBody->SetStatic();
	if (lockRotation)
		rigidBody->LockRotation();

	return rigidBody;
}

CircleColliderComponent * ComponentFactory::MakeCircleColliderComponent(float radius)
{
	CircleColliderComponent * circleCollider = new CircleColliderComponent();

	return circleCollider;
}

PolygonColliderComponent * ComponentFactory::MakePolygonCollider(Vec2 * verticies, int vertexCount)
{
	PolygonColliderComponent * polygonCollider = new PolygonColliderComponent();
	polygonCollider->SetVerticies(verticies, vertexCount);

	delete verticies; // Clear memory

	return polygonCollider;
}

BoxColliderComponent * ComponentFactory::MakeBoxCollider(float width, float height)
{
	BoxColliderComponent * boxCollider = new BoxColliderComponent(width, height);

	return boxCollider;
}

//
//MCharacterComponent * ComponentFactory::MakeMCharacterComponent()
//{
//	return new MCharacterComponent();
//}
