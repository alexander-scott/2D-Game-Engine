#include "Collision.h"


Collision::~Collision()
{
}

void Collision::CheckForCollision()
{
	if (mColliderA->GetType() == ColliderType::eCircle && mColliderB->GetType() == ColliderType::eCircle) // Circle to circle
	{
		CircletoCircleCollision();
	}
	else if (mColliderA->GetType() == ColliderType::eCircle && mColliderB->GetType() == ColliderType::ePolygon) // Circle to polygon
	{
		CircleToPolygonCollision();
	}
	else if (mColliderA->GetType() == ColliderType::ePolygon && mColliderB->GetType() == ColliderType::eCircle) // Polygon to circle
	{
		PolygonToCircleCollision();
	}
	else if (mColliderA->GetType() == ColliderType::ePolygon && mColliderB->GetType() == ColliderType::ePolygon) // Polygon to polygon
	{
		PolygonToPolygonCollision();
	}
}

void Collision::PrepareToSolve(float deltaTime)
{
	// Calculate average restitution
	mMixedRestitution = std::min(mColliderA->GetRigidbodyComponent()->GetRestitution(), mColliderB->GetRigidbodyComponent()->GetRestitution());

	// Calculate static and dynamic friction
	mMixedStaticFriction = std::sqrt(mColliderA->GetRigidbodyComponent()->GetStaticFriction() * mColliderB->GetRigidbodyComponent()->GetStaticFriction());
	mMixedDynamicFriction = std::sqrt(mColliderA->GetRigidbodyComponent()->GetDynamicFriction() * mColliderB->GetRigidbodyComponent()->GetDynamicFriction());

	for (int i = 0; i < mContactCount; ++i)
	{
		// Calculate radii from COM to contact
		Vec2 ra = mContacts[i] - mColliderA->GetTransformComponent()->GetWorldPosition();
		Vec2 rb = mContacts[i] - mColliderB->GetTransformComponent()->GetWorldPosition();

		Vec2 rv = mColliderB->GetRigidbodyComponent()->GetVelocity() + Cross(mColliderB->GetRigidbodyComponent()->GetAngularVelocity(), rb) -
			mColliderA->GetRigidbodyComponent()->GetVelocity() - Cross(mColliderA->GetRigidbodyComponent()->GetAngularVelocity(), ra);

		// Determine if we should perform a resting collision or not
		// The idea is if the only thing moving this object is gravity,
		// then the collision should be performed without any restitution
		if (rv.LenSqr() < (deltaTime * GRAVITY_VECTOR).LenSqr() + EPSILON)
			mMixedRestitution = 0.0f;
	}
}

void Collision::ResolveCollision()
{
	// Early out and positional correct if both objects have infinite mass
	if (Equal(mColliderA->GetRigidbodyComponent()->GetInverseMass() + mColliderB->GetRigidbodyComponent()->GetInverseMass(), 0))
	{
		NullVelocities();
		return;
	}

	for (int i = 0; i < mContactCount; ++i)
	{
		// Calculate radii from positions to contact
		Vec2 radiiA = mContacts[i] - mColliderA->GetTransformComponent()->GetWorldPosition();
		Vec2 radiiB = mContacts[i] - mColliderB->GetTransformComponent()->GetWorldPosition();

		// Calculate relative velocity
		Vec2 relativeVelocity = mColliderB->GetRigidbodyComponent()->GetVelocity() + Cross(mColliderB->GetRigidbodyComponent()->GetAngularVelocity(), radiiB) -
			mColliderA->GetRigidbodyComponent()->GetVelocity() - Cross(mColliderA->GetRigidbodyComponent()->GetAngularVelocity(), radiiA);

		// Relative velocity along the normal
		float contactVelocity = Dot(relativeVelocity, mNormal);

		// Do not resolve if velocities are separating
		if (contactVelocity > 0)
			return;

		float radiiACrossN = Cross(radiiA, mNormal);
		float radiiBCrossN = Cross(radiiB, mNormal);
		float inverseMassSum = mColliderA->GetRigidbodyComponent()->GetInverseMass() + mColliderB->GetRigidbodyComponent()->GetInverseMass() + 
			Sqr(radiiACrossN) * mColliderA->GetRigidbodyComponent()->GetInverseIntertia() + Sqr(radiiBCrossN) * mColliderB->GetRigidbodyComponent()->GetInverseIntertia();

		// Calculate impulse scalar
		float impulseScalar = -(1.0f + mMixedRestitution) * contactVelocity;
		impulseScalar /= inverseMassSum;
		impulseScalar /= (float)mContactCount;

		// Apply impulse
		Vec2 impulse = mNormal * impulseScalar;
		mColliderA->GetRigidbodyComponent()->ApplyImpulse(-impulse, radiiA);
		mColliderB->GetRigidbodyComponent()->ApplyImpulse(impulse, radiiB);

		// Friction impulse
		relativeVelocity = mColliderB->GetRigidbodyComponent()->GetVelocity() + Cross(mColliderB->GetRigidbodyComponent()->GetAngularVelocity(), radiiB) -
			mColliderA->GetRigidbodyComponent()->GetVelocity() - Cross(mColliderA->GetRigidbodyComponent()->GetAngularVelocity(), radiiA);

		Vec2 t = relativeVelocity - (mNormal * Dot(relativeVelocity, mNormal));
		t.Normalize();

		// ImpulseScalar tangent magnitude
		float impulseScalarTangentMagnitude = -Dot(relativeVelocity, t);
		impulseScalarTangentMagnitude /= inverseMassSum;
		impulseScalarTangentMagnitude /= (float)mContactCount;

		// Don't apply tiny friction impulses
		if (Equal(impulseScalarTangentMagnitude, 0.0f))
			return;

		// Coulomb's law
		Vec2 tangentImpulse;
		if (std::abs(impulseScalarTangentMagnitude) < impulseScalar * mMixedStaticFriction)
			tangentImpulse = t * impulseScalarTangentMagnitude;
		else
			tangentImpulse = t * -impulseScalar * mMixedDynamicFriction;

		// Apply friction impulse
		mColliderA->GetRigidbodyComponent()->ApplyImpulse(-tangentImpulse, radiiA);
		mColliderB->GetRigidbodyComponent()->ApplyImpulse(tangentImpulse, radiiB);
	}
}

void Collision::PenetrationCorrection()
{
	float allowance = 0.05f; // Penetration allowance
	float percent = 0.4f; // Penetration percentage to correct

	Vec2 correction = (std::max(mPenetration - allowance, 0.0f) / (mColliderA->GetRigidbodyComponent()->GetInverseMass() + mColliderB->GetRigidbodyComponent()->GetInverseMass())) * mNormal * percent;
	mColliderA->GetTransformComponent()->SetWorldPosition(mColliderA->GetTransformComponent()->GetWorldPosition() - correction * mColliderA->GetRigidbodyComponent()->GetInverseMass());
	mColliderB->GetTransformComponent()->SetWorldPosition(mColliderB->GetTransformComponent()->GetWorldPosition() + correction * mColliderB->GetRigidbodyComponent()->GetInverseMass());
}

void Collision::NullVelocities()
{
	mColliderA->GetRigidbodyComponent()->SetVelocity(Vec2(0, 0));
	mColliderB->GetRigidbodyComponent()->SetVelocity(Vec2(0, 0));
}

void Collision::CircletoCircleCollision()
{
	CircleColliderComponent *A = reinterpret_cast<CircleColliderComponent *>(mColliderA);
	CircleColliderComponent *B = reinterpret_cast<CircleColliderComponent *>(mColliderB);

	// Calculate translational vector, which is normal
	mNormal = B->GetTransformComponent()->GetWorldPosition() - A->GetTransformComponent()->GetWorldPosition();

	float distSquared = mNormal.LenSqr();
	float radius = A->GetRadius() + B->GetRadius();

	// Not in contact
	if (distSquared >= radius * radius)
	{
		mContactCount = 0;
		return;
	}

	float distance = std::sqrt(distSquared);

	mContactCount = 1;

	if (distance == 0.0f)
	{
		mPenetration = A->GetRadius();
		mNormal = Vec2(1, 0);
		mContacts[0] = A->GetTransformComponent()->GetWorldPosition();
	}
	else
	{
		mPenetration = radius - distance;
		mNormal = mNormal / distance; // Faster than using Normalized since we already performed sqrt
		mContacts[0] = mNormal * A->GetRadius() + A->GetTransformComponent()->GetWorldPosition();
	}
}

void Collision::CircleToPolygonCollision()
{
	CircleColliderComponent *A = reinterpret_cast<CircleColliderComponent *>(mColliderA);
	PolygonColliderComponent *B = reinterpret_cast<PolygonColliderComponent *>(mColliderB);

	mContactCount = 0;

	// Transform circle center to Polygon model space
	Vec2 center = mColliderA->GetTransformComponent()->GetWorldPosition();
	center = mColliderB->GetRigidbodyComponent()->GetOrientationMatrix().Transpose() * (center - mColliderB->GetTransformComponent()->GetWorldPosition());

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
		mContactCount = 1;
		mNormal = -(B->GetRigidbodyComponent()->GetOrientationMatrix() * B->Normals[faceNormal]);
		mContacts[0] = mNormal * A->GetRadius() + mColliderA->GetTransformComponent()->GetWorldPosition();
		mPenetration = A->GetRadius();
		return;
	}

	// Determine which voronoi region of the edge center of circle lies within
	float dot1 = Dot(center - vertex1, vertex2 - vertex1);
	float dot2 = Dot(center - vertex2, vertex1 - vertex2);
	mPenetration = A->GetRadius() - separation;

	// Closest to vertex1
	if (dot1 <= 0.0f)
	{
		if (DistSqr(center, vertex1) > A->GetRadius() * A->GetRadius())
			return;

		mContactCount = 1;
		Vec2 n = vertex1 - center;
		n = B->GetRigidbodyComponent()->GetOrientationMatrix() * n;
		n.Normalize();
		mNormal = n;
		vertex1 = B->GetRigidbodyComponent()->GetOrientationMatrix() * vertex1 + mColliderB->GetTransformComponent()->GetWorldPosition();
		mContacts[0] = vertex1;
	}
	else if (dot2 <= 0.0f) // Closest to vertex2
	{
		if (DistSqr(center, vertex2) > A->GetRadius() * A->GetRadius())
			return;

		mContactCount = 1;
		Vec2 n = vertex2 - center;
		vertex2 = B->GetRigidbodyComponent()->GetOrientationMatrix() * vertex2 + mColliderB->GetTransformComponent()->GetWorldPosition();
		mContacts[0] = vertex2;
		n = B->GetRigidbodyComponent()->GetOrientationMatrix() * n;
		n.Normalize();
		mNormal = n;
	}
	else // Closest to face
	{
		Vec2 n = B->Normals[faceNormal];
		if (Dot(center - vertex1, n) > A->GetRadius())
			return;

		n = B->GetRigidbodyComponent()->GetOrientationMatrix() * n;
		mNormal = -n;
		mContacts[0] = mNormal * A->GetRadius() + mColliderA->GetTransformComponent()->GetWorldPosition();
		mContactCount = 1;
	}
}

void Collision::PolygonToCircleCollision()
{
	ColliderComponent* cC = mColliderA;
	mColliderA = mColliderB;
	mColliderB = cC;
	mNormal = -mNormal;

	CircleToPolygonCollision();
}

void Collision::PolygonToPolygonCollision()
{
	PolygonColliderComponent *A = reinterpret_cast<PolygonColliderComponent *>(mColliderA);
	PolygonColliderComponent *B = reinterpret_cast<PolygonColliderComponent *>(mColliderB);
	mContactCount = 0;

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
	mNormal = flip ? -refFaceNormal : refFaceNormal;

	// Keep points behind reference face
	int cp = 0; // Clipped points behind reference face
	float separation = Dot(refFaceNormal, incidentFace[0]) - refC;
	if (separation <= 0.0f)
	{
		mContacts[cp] = incidentFace[0];
		mPenetration = -separation;
		++cp;
	}
	else
		mPenetration = 0;

	separation = Dot(refFaceNormal, incidentFace[1]) - refC;
	if (separation <= 0.0f)
	{
		mContacts[cp] = incidentFace[1];

		mPenetration += -separation;
		++cp;

		// Average penetration
		mPenetration /= (float)cp;
	}

	mContactCount = cp;
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
