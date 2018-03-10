#include "PolygonColliderComponent.h"



PolygonColliderComponent::PolygonColliderComponent(TransformComponent* trans, RigidBodyComponent* rb, string componentType)
	: ColliderComponent(componentType)
{
	_transformComponent = trans;
	_rigidyBodyComponent = rb;
}

PolygonColliderComponent::~PolygonColliderComponent()
{
}

void PolygonColliderComponent::ComputeMass(float density)
{
	if (_rigidyBodyComponent->GetInverseMass() == 0)
		return;

	// Calculate centroid and moment of interia
	_centre = Vec2(0.0f, 0.0f); // centroid
	float area = 0.0f;
	float intertia = 0.0f;
	const float inv3 = 1.0f / 3.0f;

	for (int i = 0; i < VertexCount; ++i)
	{
		// Triangle vertices, third vertex implied as (0, 0)
		Vec2 p1(Vertices[i]);
		int i2 = i + 1 < VertexCount ? i + 1 : 0;
		Vec2 p2(Vertices[i2]);

		float D = Cross(p1, p2);
		float triangleArea = 0.5f * D;

		area += triangleArea;

		// Use area to weight the centroid average, not just vertex position
		_centre += triangleArea * inv3 * (p1 + p2);

		float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
		float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
		intertia += (0.25f * inv3 * D) * (intx2 + inty2);
	}

	_centre *= 1.0f / area;

	// Translate vertices to centroid (make the centroid (0, 0) for the polygon in model space)
	for (int i = 0; i < VertexCount; ++i)
		Vertices[i] -= _centre;

	_rigidyBodyComponent->SetMass(density * area);
	_rigidyBodyComponent->SetInverseMass(_rigidyBodyComponent->GetMass() ? 1.0f / _rigidyBodyComponent->GetMass() : 0.0f);
	_rigidyBodyComponent->SetIntertia(intertia * density);
	_rigidyBodyComponent->SetInverseIntertia(_rigidyBodyComponent->GetIntertia() ? 1.0f / _rigidyBodyComponent->GetIntertia() : 0.0f);
}

Rect PolygonColliderComponent::GetRect()
{
	if (VertexCount == 4)
	{
		Vec2 pos = _transformComponent->GetWorldPosition();
		Rect r;
		r.LeftX = (int)pos.x;
		r.BotY = (int)pos.y + (int)(_halfHeight * 2);
		r.RightX = (int)pos.x + (int)(_halfWidth * 2);
		r.TopY = (int)pos.y;
		r.Centre = Vec2(pos.x + _halfWidth, pos.y + _halfHeight);
		return r;
	}
	else
		throw;

	return Rect();
}

void PolygonColliderComponent::SetVerticies(Vec2 * vertices, int count)
{
	// No hulls with less than 3 vertices (ensure actual polygon)
	assert(count > 2 && count <= MAX_POLY_VERTEX_COUNT);
	count = std::min((int)count, MAX_POLY_VERTEX_COUNT);

	// Find the right most point on the hull
	int rightMost = 0;
	float highestXCoord = vertices[0].x;
	for (int i = 1; i < count; ++i)
	{
		float x = vertices[i].x;
		if (x > highestXCoord)
		{
			highestXCoord = x;
			rightMost = i;
		}
		else if (x == highestXCoord) //  If matching x then take farthest negative y
		{
			if (vertices[i].y < vertices[rightMost].y)
				rightMost = i;
		}	
	}

	int hull[MAX_POLY_VERTEX_COUNT];
	int outCount = 0;
	int indexHull = rightMost;

	for (;;)
	{
		hull[outCount] = indexHull;

		// Search for next index that wraps around the hull
		int nextHullIndex = 0;
		for (int i = 1; i < (int)count; ++i)
		{
			// Skip if same coordinate
			if (nextHullIndex == indexHull)
			{
				nextHullIndex = i;
				continue;
			}

			Vec2 e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
			Vec2 e2 = vertices[i] - vertices[hull[outCount]];
			float c = Cross(e1, e2);
			if (c < 0.0f)
				nextHullIndex = i;

			// Cross product is zero then e vectors are on same line
			if (c == 0.0f && e2.LenSqr() > e1.LenSqr())
				nextHullIndex = i;
		}

		++outCount;
		indexHull = nextHullIndex;

		// Break out if we've wraped-around
		if (nextHullIndex == rightMost)
		{
			VertexCount = outCount;
			break;
		}
	}

	// Copy vertices into shape's vertices
	for (int i = 0; i < VertexCount; ++i)
		Vertices[i] = vertices[hull[i]];

	// Compute face normals
	for (int i1 = 0; i1 < VertexCount; ++i1)
	{
		int i2 = i1 + 1 < VertexCount ? i1 + 1 : 0;
		Vec2 face = Vertices[i2] - Vertices[i1];

		// Ensure no zero-length edge
		assert(face.LenSqr() > EPSILON * EPSILON);

		// Calculate normal with 2D cross product between vector and scalar
		Normals[i1] = Vec2(face.y, -face.x);
		Normals[i1].Normalize();
	}
}

// The extreme point along a direction within a polygon
Vec2 PolygonColliderComponent::GetSupport(const Vec2& dir)
{
	float bestProjection = -FLT_MAX;
	Vec2 bestVertex;

	for (int i = 0; i < VertexCount; ++i)
	{
		Vec2 v = Vertices[i];
		float projection = Dot(v, dir);

		if (projection > bestProjection)
		{
			bestVertex = v;
			bestProjection = projection;
		}
	}

	return bestVertex;
}
