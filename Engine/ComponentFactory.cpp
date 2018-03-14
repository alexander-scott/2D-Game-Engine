#include "ComponentFactory.h"

TransformComponent * ComponentFactory::MakeTransformComponent(Vec2 position, float rotation, float scale)
{
	TransformComponent * transform = new TransformComponent(position, rotation, scale);

	return transform;
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
