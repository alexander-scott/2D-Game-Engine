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

CircleColliderComponent * ComponentFactory::MakeCircleColliderComponent(float radius, TransformComponent * transform, RigidBodyComponent * rigidbody)
{
	if (transform == nullptr)
		throw std::exception("This object requires a transform component.");
	if (rigidbody == nullptr)
		throw std::exception("This object requires a rigidbody component.");

	CircleColliderComponent * circleCollider = new CircleColliderComponent(transform, rigidbody);
	circleCollider->SetRadius(radius * transform->GetWorldScale());
	circleCollider->ComputeMass(rigidbody->GetDensity());

	return circleCollider;
}

PolygonColliderComponent * ComponentFactory::MakePolygonCollider(Vec2 * verticies, int vertexCount, TransformComponent * transform, RigidBodyComponent * rigidbody)
{
	if (transform == nullptr)
		throw std::exception("This object requires a transform component.");
	if (rigidbody == nullptr)
		throw std::exception("This object requires a rigidbody component.");

	PolygonColliderComponent * polygonCollider = new PolygonColliderComponent(transform, rigidbody);
	polygonCollider->SetVerticies(verticies, vertexCount);
	polygonCollider->ComputeMass(rigidbody->GetDensity());

	delete verticies; // Clear memory

	return polygonCollider;
}

BoxColliderComponent * ComponentFactory::MakeBoxCollider(float width, float height, TransformComponent * transform, RigidBodyComponent * rigidBody)
{
	if (transform == nullptr)
		throw std::exception("This object requires a transform component.");
	if (rigidBody == nullptr)
		throw std::exception("This object requires a rigidbody component.");

	BoxColliderComponent * boxCollider = new BoxColliderComponent(transform, rigidBody, width, height);
	boxCollider->ComputeMass(rigidBody->GetDensity());

	return boxCollider;
}
