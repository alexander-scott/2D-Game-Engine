#include "CircleColliderComponent.h"

CircleColliderComponent::CircleColliderComponent()
	: ColliderComponent("CircleColliderComponent")
{
}

void CircleColliderComponent::Start()
{
	ComputeMass(GetRigidbodyComponent()->GetDensity());
	_radius = _baseRadius * GetTransformComponent()->GetWorldScale();
}

void CircleColliderComponent::ComputeMass(float density)
{
	if (_rigidyBodyComponent->GetInverseMass() == 0)
		return;

	_rigidyBodyComponent->SetMass(PI * _radius * _radius * density);
	_rigidyBodyComponent->SetInverseMass((_rigidyBodyComponent->GetMass()) ? 1.0f / _rigidyBodyComponent->GetMass() : 0.0f);
	_rigidyBodyComponent->SetIntertia(_rigidyBodyComponent->GetMass() * _radius * _radius);
	_rigidyBodyComponent->SetInverseIntertia((_rigidyBodyComponent->GetIntertia()) ? 1.0f / _rigidyBodyComponent->GetIntertia() : 0.0f);
}

Rect CircleColliderComponent::GetRect()
{
	Vec2 pos = _transformComponent->GetWorldPosition();
	Rect r;
	r.LeftX = (int)pos.x;
	r.TopY = (int)pos.y;
	r.RightX = (int)pos.x + (int)_radius;
	r.BotY = (int)pos.y + (int)_radius;
	r.Centre = Vec2(pos.x + (_radius / 2), pos.y + (_radius / 2));

	return r;
}