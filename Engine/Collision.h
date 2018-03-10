#pragma once

#include "ColliderComponent.h"
#include "CircleColliderComponent.h"
#include "PolygonColliderComponent.h"

class Collision
{
public:
	Collision(ColliderComponent* a, ColliderComponent* b) : _colliderA(a), _colliderB(b) { }
	~Collision();

	int GetContactCount() { return _contactCount; }

	void CheckForCollision();				// Determine if there was a collision and generate contact information
	void PrepareToSolve(float deltaTime);   // Precalculations for impulse solving
	void ResolveCollision();				// Resolve impulse and apply to rigidbody
	void PenetrationCorrection();			// Correction of positional penetration

private:
	void CircletoCircleCollision();
	void CircleToPolygonCollision();
	void PolygonToCircleCollision();
	void PolygonToPolygonCollision();

	void NullVelocities();

	float GetFurthestPenetration(int* faceIndex, PolygonColliderComponent* A, PolygonColliderComponent *B);
	void FindIncidentFace(Vec2 *v, PolygonColliderComponent *RefPoly, PolygonColliderComponent *IncPoly, int referenceIndex);
	int Clip(Vec2 n, float c, Vec2 *face);

	ColliderComponent*		_colliderA;
	ColliderComponent*		_colliderB;

	float					_penetration;			 // Depth of penetration from collision
	Vec2					_normal;				 // From A to B
	Vec2					_contacts[2];			 // Points of contact during collision
	int						_contactCount;			 // Number of contacts that occured during collision
	float					_mixedRestitution;       // Mixed restitution between the two colliders
	float					_mixedDynamicFriction;   // Mixed dynamic friction between the two colliders
	float					_mixedStaticFriction;	 // Mixed static friction between the two colliders
};

