#include "Collision.h"


Collision::~Collision()
{
}

void Collision::CheckForCollision()
{
	if (_colliderA->GetType() == ColliderType::eCircle && _colliderB->GetType() == ColliderType::eCircle) // Circle to circle
	{
		CircletoCircleCollision();
	}
	else if (_colliderA->GetType() == ColliderType::eCircle && _colliderB->GetType() == ColliderType::ePolygon) // Circle to polygon
	{
		CircleToPolygonCollision();
	}
	else if (_colliderA->GetType() == ColliderType::ePolygon && _colliderB->GetType() == ColliderType::eCircle) // Polygon to circle
	{
		PolygonToCircleCollision();
	}
	else if (_colliderA->GetType() == ColliderType::ePolygon && _colliderB->GetType() == ColliderType::ePolygon) // Polygon to polygon
	{
		PolygonToPolygonCollision();
	}
}

void Collision::PrepareToSolve(float deltaTime)
{
	// Calculate average restitution
	_mixedRestitution = std::min(_colliderA->GetRigidbodyComponent()->GetRestitution(), _colliderB->GetRigidbodyComponent()->GetRestitution());

	// Calculate static and dynamic friction
	_mixedStaticFriction = std::sqrt(_colliderA->GetRigidbodyComponent()->GetStaticFriction() * _colliderB->GetRigidbodyComponent()->GetStaticFriction());
	_mixedDynamicFriction = std::sqrt(_colliderA->GetRigidbodyComponent()->GetDynamicFriction() * _colliderB->GetRigidbodyComponent()->GetDynamicFriction());

	for (int i = 0; i < _contactCount; ++i)
	{
		// Calculate radii from COM to contact
		Vec2 ra = _contacts[i] - _colliderA->GetTransformComponent()->GetWorldPosition();
		Vec2 rb = _contacts[i] - _colliderB->GetTransformComponent()->GetWorldPosition();

		Vec2 rv = _colliderB->GetRigidbodyComponent()->GetVelocity() + Cross(_colliderB->GetRigidbodyComponent()->GetAngularVelocity(), rb) -
			_colliderA->GetRigidbodyComponent()->GetVelocity() - Cross(_colliderA->GetRigidbodyComponent()->GetAngularVelocity(), ra);

		// Determine if we should perform a resting collision or not
		// The idea is if the only thing moving this object is gravity,
		// then the collision should be performed without any restitution
		if (rv.LenSqr() < (deltaTime * GRAVITY_VECTOR).LenSqr() + EPSILON)
			_mixedRestitution = 0.0f;
	}
}

void Collision::ResolveCollision()
{
	// Early out and positional correct if both objects have infinite mass
	if (Equal(_colliderA->GetRigidbodyComponent()->GetInverseMass() + _colliderB->GetRigidbodyComponent()->GetInverseMass(), 0))
	{
		NullVelocities();
		return;
	}

	for (int i = 0; i < _contactCount; ++i)
	{
		// Calculate radii from positions to contact
		Vec2 radiiA = _contacts[i] - _colliderA->GetTransformComponent()->GetWorldPosition();
		Vec2 radiiB = _contacts[i] - _colliderB->GetTransformComponent()->GetWorldPosition();

		// Calculate relative velocity
		Vec2 relativeVelocity = _colliderB->GetRigidbodyComponent()->GetVelocity() + Cross(_colliderB->GetRigidbodyComponent()->GetAngularVelocity(), radiiB) -
			_colliderA->GetRigidbodyComponent()->GetVelocity() - Cross(_colliderA->GetRigidbodyComponent()->GetAngularVelocity(), radiiA);

		// Relative velocity along the normal
		float contactVelocity = Dot(relativeVelocity, _normal);

		// Do not resolve if velocities are separating
		if (contactVelocity > 0)
			return;

		float radiiACrossN = Cross(radiiA, _normal);
		float radiiBCrossN = Cross(radiiB, _normal);
		float inverseMassSum = _colliderA->GetRigidbodyComponent()->GetInverseMass() + _colliderB->GetRigidbodyComponent()->GetInverseMass() + 
			Sqr(radiiACrossN) * _colliderA->GetRigidbodyComponent()->GetInverseIntertia() + Sqr(radiiBCrossN) * _colliderB->GetRigidbodyComponent()->GetInverseIntertia();

		// Calculate impulse scalar
		float impulseScalar = -(1.0f + _mixedRestitution) * contactVelocity;
		impulseScalar /= inverseMassSum;
		impulseScalar /= (float)_contactCount;

		// Apply impulse
		Vec2 impulse = _normal * impulseScalar;
		_colliderA->GetRigidbodyComponent()->ApplyImpulse(-impulse, radiiA);
		_colliderB->GetRigidbodyComponent()->ApplyImpulse(impulse, radiiB);

		// Friction impulse
		relativeVelocity = _colliderB->GetRigidbodyComponent()->GetVelocity() + Cross(_colliderB->GetRigidbodyComponent()->GetAngularVelocity(), radiiB) -
			_colliderA->GetRigidbodyComponent()->GetVelocity() - Cross(_colliderA->GetRigidbodyComponent()->GetAngularVelocity(), radiiA);

		Vec2 t = relativeVelocity - (_normal * Dot(relativeVelocity, _normal));
		t.Normalize();

		// ImpulseScalar tangent magnitude
		float impulseScalarTangentMagnitude = -Dot(relativeVelocity, t);
		impulseScalarTangentMagnitude /= inverseMassSum;
		impulseScalarTangentMagnitude /= (float)_contactCount;

		// Don't apply tiny friction impulses
		if (Equal(impulseScalarTangentMagnitude, 0.0f))
			return;

		// Coulomb's law
		Vec2 tangentImpulse;
		if (std::abs(impulseScalarTangentMagnitude) < impulseScalar * _mixedStaticFriction)
			tangentImpulse = t * impulseScalarTangentMagnitude;
		else
			tangentImpulse = t * -impulseScalar * _mixedDynamicFriction;

		// Apply friction impulse
		_colliderA->GetRigidbodyComponent()->ApplyImpulse(-tangentImpulse, radiiA);
		_colliderB->GetRigidbodyComponent()->ApplyImpulse(tangentImpulse, radiiB);
	}
}

void Collision::PenetrationCorrection()
{
	float allowance = 0.05f; // Penetration allowance
	float percent = 0.4f; // Penetration percentage to correct

	Vec2 correction = (std::max(_penetration - allowance, 0.0f) / (_colliderA->GetRigidbodyComponent()->GetInverseMass() + _colliderB->GetRigidbodyComponent()->GetInverseMass())) * _normal * percent;
	_colliderA->GetTransformComponent()->SetWorldPosition(_colliderA->GetTransformComponent()->GetWorldPosition() - correction * _colliderA->GetRigidbodyComponent()->GetInverseMass());
	_colliderB->GetTransformComponent()->SetWorldPosition(_colliderB->GetTransformComponent()->GetWorldPosition() + correction * _colliderB->GetRigidbodyComponent()->GetInverseMass());
}

void Collision::NullVelocities()
{
	_colliderA->GetRigidbodyComponent()->SetVelocity(Vec2(0, 0));
	_colliderB->GetRigidbodyComponent()->SetVelocity(Vec2(0, 0));
}

void Collision::CircletoCircleCollision()
{
	CircleColliderComponent *A = reinterpret_cast<CircleColliderComponent *>(_colliderA);
	CircleColliderComponent *B = reinterpret_cast<CircleColliderComponent *>(_colliderB);

	// Calculate translational vector, which is normal
	_normal = B->GetTransformComponent()->GetWorldPosition() - A->GetTransformComponent()->GetWorldPosition();

	float distSquared = _normal.LenSqr();
	float radius = A->GetRadius() + B->GetRadius();

	// Not in contact
	if (distSquared >= radius * radius)
	{
		_contactCount = 0;
		return;
	}

	float distance = std::sqrt(distSquared);

	_contactCount = 1;

	if (distance == 0.0f)
	{
		_penetration = A->GetRadius();
		_normal = Vec2(1, 0);
		_contacts[0] = A->GetTransformComponent()->GetWorldPosition();
	}
	else
	{
		_penetration = radius - distance;
		_normal = _normal / distance; // Faster than using Normalized since we already performed sqrt
		_contacts[0] = _normal * A->GetRadius() + A->GetTransformComponent()->GetWorldPosition();
	}
}

void Collision::CircleToPolygonCollision()
{
	CircleColliderComponent *A = reinterpret_cast<CircleColliderComponent *>(_colliderA);
	PolygonColliderComponent *B = reinterpret_cast<PolygonColliderComponent *>(_colliderB);

	_contactCount = 0;

	// Transform circle center to Polygon model space
	Vec2 center = _colliderA->GetTransformComponent()->GetWorldPosition();
	center = _colliderB->GetRigidbodyComponent()->GetOrientationMatrix().Transpose() * (center - _colliderB->GetTransformComponent()->GetWorldPosition());

	// Find edge with minimum penetration
	// Exact concept as using support points in Polygon vs Polygon
	float separation = -FLT_MAX;
	int faceNormal = 0;
	for (int i = 0; i < B->VertexCount; ++i)
	{
		float sep = Dot(B->Normals[i], center - B->Vertices[i]);

		if (sep > A->GetRadius())
			return;

		if (sep > separation)
		{
			separation = sep;
			faceNormal = i;
		}
	}

	// Grab face's vertices
	Vec2 vertex1 = B->Vertices[faceNormal];
	int index2 = faceNormal + 1 < B->VertexCount ? faceNormal + 1 : 0;
	Vec2 vertex2 = B->Vertices[index2];

	// Check to see if center is within polygon
	if (separation < EPSILON)
	{
		_contactCount = 1;
		_normal = -(B->GetRigidbodyComponent()->GetOrientationMatrix() * B->Normals[faceNormal]);
		_contacts[0] = _normal * A->GetRadius() + _colliderA->GetTransformComponent()->GetWorldPosition();
		_penetration = A->GetRadius();
		return;
	}

	// Determine which voronoi region of the edge center of circle lies within
	float dot1 = Dot(center - vertex1, vertex2 - vertex1);
	float dot2 = Dot(center - vertex2, vertex1 - vertex2);
	_penetration = A->GetRadius() - separation;

	// Closest to vertex1
	if (dot1 <= 0.0f)
	{
		if (DistSqr(center, vertex1) > A->GetRadius() * A->GetRadius())
			return;

		_contactCount = 1;
		Vec2 n = vertex1 - center;
		n = B->GetRigidbodyComponent()->GetOrientationMatrix() * n;
		n.Normalize();
		_normal = n;
		vertex1 = B->GetRigidbodyComponent()->GetOrientationMatrix() * vertex1 + _colliderB->GetTransformComponent()->GetWorldPosition();
		_contacts[0] = vertex1;
	}
	else if (dot2 <= 0.0f) // Closest to vertex2
	{
		if (DistSqr(center, vertex2) > A->GetRadius() * A->GetRadius())
			return;

		_contactCount = 1;
		Vec2 n = vertex2 - center;
		vertex2 = B->GetRigidbodyComponent()->GetOrientationMatrix() * vertex2 + _colliderB->GetTransformComponent()->GetWorldPosition();
		_contacts[0] = vertex2;
		n = B->GetRigidbodyComponent()->GetOrientationMatrix() * n;
		n.Normalize();
		_normal = n;
	}
	else // Closest to face
	{
		Vec2 n = B->Normals[faceNormal];
		if (Dot(center - vertex1, n) > A->GetRadius())
			return;

		n = B->GetRigidbodyComponent()->GetOrientationMatrix() * n;
		_normal = -n;
		_contacts[0] = _normal * A->GetRadius() + _colliderA->GetTransformComponent()->GetWorldPosition();
		_contactCount = 1;
	}
}

void Collision::PolygonToCircleCollision()
{
	ColliderComponent* cC = _colliderA;
	_colliderA = _colliderB;
	_colliderB = cC;
	_normal = -_normal;

	CircleToPolygonCollision();
}

void Collision::PolygonToPolygonCollision()
{
	PolygonColliderComponent *A = reinterpret_cast<PolygonColliderComponent *>(_colliderA);
	PolygonColliderComponent *B = reinterpret_cast<PolygonColliderComponent *>(_colliderB);
	_contactCount = 0;

	// Check for a separating axis with A's face planes
	int faceA;
	float penetrationA = GetFurthestPenetration(&faceA, A, B);
	if (penetrationA >= 0.0f)
		return;

	// Check for a separating axis with B's face planes
	int faceB;
	float penetrationB = GetFurthestPenetration(&faceB, B, A);
	if (penetrationB >= 0.0f)
		return;

	int referenceIndex;
	bool flip; // Always point from a to b

	PolygonColliderComponent *RefPoly; // Reference
	PolygonColliderComponent *IncPoly; // Incident

	// Determine which shape contains reference face
	if (BiasGreaterThan(penetrationA, penetrationB))
	{
		RefPoly = A;
		IncPoly = B;
		referenceIndex = faceA;
		flip = false;
	}

	else
	{
		RefPoly = B;
		IncPoly = A;
		referenceIndex = faceB;
		flip = true;
	}

	// World space incident face
	Vec2 incidentFace[2];
	FindIncidentFace(incidentFace, RefPoly, IncPoly, referenceIndex);

	// Setup reference face vertices
	Vec2 v1 = RefPoly->Vertices[referenceIndex];
	referenceIndex = referenceIndex + 1 == RefPoly->VertexCount ? 0 : referenceIndex + 1;
	Vec2 v2 = RefPoly->Vertices[referenceIndex];

	// Transform vertices to world space
	v1 = RefPoly->GetRigidbodyComponent()->GetOrientationMatrix() * v1 + RefPoly->GetTransformComponent()->GetWorldPosition();
	v2 = RefPoly->GetRigidbodyComponent()->GetOrientationMatrix() * v2 + RefPoly->GetTransformComponent()->GetWorldPosition();

	// Calculate reference face side normal in world space
	Vec2 sidePlaneNormal = (v2 - v1);
	sidePlaneNormal.Normalize();

	// Orthogonalize
	Vec2 refFaceNormal(sidePlaneNormal.y, -sidePlaneNormal.x);

	float refC = Dot(refFaceNormal, v1);
	float negSide = -Dot(sidePlaneNormal, v1);
	float posSide = Dot(sidePlaneNormal, v2);

	// Clip incident face to reference face side planes. Due to floating point error, possible to not have required points
	if (Clip(-sidePlaneNormal, negSide, incidentFace) < 2)
		return; 

	if (Clip(sidePlaneNormal, posSide, incidentFace) < 2)
		return; 

	// Flip
	_normal = flip ? -refFaceNormal : refFaceNormal;

	// Keep points behind reference face
	int cp = 0; // Clipped points behind reference face
	float separation = Dot(refFaceNormal, incidentFace[0]) - refC;
	if (separation <= 0.0f)
	{
		_contacts[cp] = incidentFace[0];
		_penetration = -separation;
		++cp;
	}
	else
		_penetration = 0;

	separation = Dot(refFaceNormal, incidentFace[1]) - refC;
	if (separation <= 0.0f)
	{
		_contacts[cp] = incidentFace[1];

		_penetration += -separation;
		++cp;

		// Average penetration
		_penetration /= (float)cp;
	}

	_contactCount = cp;
}

float Collision::GetFurthestPenetration(int * faceIndex, PolygonColliderComponent * A, PolygonColliderComponent * B)
{
	float bestDistance = -100000;
	int bestIndex;

	for (int i = 0; i < A->VertexCount; ++i)
	{
		// Retrieve a face normal from A
		Vec2 n = A->Normals[i];
		Vec2 nw = A->GetRigidbodyComponent()->GetOrientationMatrix() * n;

		// Transform face normal into B's model space
		Mat2 buT = B->GetRigidbodyComponent()->GetOrientationMatrix().Transpose();
		n = buT * nw;

		// Retrieve support point from B along -n
		Vec2 s = B->GetSupport(-n);

		// Retrieve vertex on face from A, transform into B's model space
		Vec2 v = A->Vertices[i];
		v = A->GetRigidbodyComponent()->GetOrientationMatrix() * v + A->GetTransformComponent()->GetWorldPosition();
		v -= B->GetTransformComponent()->GetWorldPosition();
		v = buT * v;

		// Compute penetration distance (in B's model space)
		float d = Dot(n, s - v);

		// Store greatest distance
		if (d > bestDistance)
		{
			bestDistance = d;
			bestIndex = i;
		}
	}

	*faceIndex = bestIndex;
	return bestDistance;
}

void Collision::FindIncidentFace(Vec2 * v, PolygonColliderComponent * RefPoly, PolygonColliderComponent * IncPoly, int referenceIndex)
{
	Vec2 referenceNormal = RefPoly->Normals[referenceIndex];

	// Calculate normal in incident's frame of reference
	referenceNormal = RefPoly->GetRigidbodyComponent()->GetOrientationMatrix() * referenceNormal; // To world space
	referenceNormal = IncPoly->GetRigidbodyComponent()->GetOrientationMatrix().Transpose() * referenceNormal; // To incident's model space

	// Find most anti-normal face on incident polygon
	int incidentFace = 0;
	float minDot = FLT_MAX;
	for (int i = 0; i < IncPoly->VertexCount; ++i)
	{
		float dot = Dot(referenceNormal, IncPoly->Normals[i]);
		if (dot < minDot)
		{
			minDot = dot;
			incidentFace = i;
		}
	}

	// Assign face vertices for incidentFace
	v[0] = IncPoly->GetRigidbodyComponent()->GetOrientationMatrix() * IncPoly->Vertices[incidentFace] + IncPoly->GetTransformComponent()->GetWorldPosition();
	incidentFace = incidentFace + 1 >= (int)IncPoly->VertexCount ? 0 : incidentFace + 1;
	v[1] = IncPoly->GetRigidbodyComponent()->GetOrientationMatrix() * IncPoly->Vertices[incidentFace] + IncPoly->GetTransformComponent()->GetWorldPosition();
}

int Collision::Clip(Vec2 n, float c, Vec2 * face)
{
	int sp = 0;
	Vec2 out[2] = {
		face[0],
		face[1]
	};

	// Retrieve distances from each endpoint to the line
	float d1 = Dot(n, face[0]) - c;
	float d2 = Dot(n, face[1]) - c;

	// If negative (behind plane) clip
	if (d1 <= 0.0f) out[sp++] = face[0];
	if (d2 <= 0.0f) out[sp++] = face[1];

	// If the points are on different sides of the plane
	if (d1 * d2 < 0.0f) // less than to ignore -0.0f
	{
		// Push interesection point
		float alpha = d1 / (d1 - d2);
		out[sp] = face[0] + alpha * (face[1] - face[0]);
		++sp;
	}

	// Assign our new converted values
	face[0] = out[0];
	face[1] = out[1];

	assert(sp != 3);

	return sp;
}
