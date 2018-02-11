#include "TransformComponent.h"

TransformComponent::TransformComponent(Vec2 localPosition, float localRotation, float localScale)
	: IComponent(ComponentType::eTransformComponent)
{
	_hasChanged = false;

	_localPosition = localPosition;
	_localScale = localScale;
	_localRotation = localRotation;

	_parent = nullptr;
}

void TransformComponent::SetLocalPosition(Vec2 position)
{
	if (position.x != _localPosition.x || position.y != _localPosition.y)
	{
		_hasChanged = true;
	}

	_localPosition = position;
}

void TransformComponent::SetLocalScale(float scale)
{
	if (scale != _localScale)
	{
		_hasChanged = true;
	}

	_localScale = scale;
}

void TransformComponent::SetLocalRotation(float rot)
{
	if (rot != _localRotation)
	{
		_hasChanged = true;
	}

	_localRotation = rot;
}

float TransformComponent::GetLocalRotation() const
{
	return _localRotation;
}

float TransformComponent::GetLocalScale() const
{
	return _localScale;
}

Vec2 TransformComponent::GetLocalPosition() const
{
	return _localPosition;
}

void TransformComponent::SetWorldPosition(Vec2 position)
{
	// Calculate the new position
	Vec2 newPos;
	if (_parent != nullptr)
		newPos = position - _parent->GetWorldPosition();
	else
		newPos = position;

	// If the new position is different to the old postion set hasChanged to true
	if (newPos.x != _localPosition.x || newPos.y != _localPosition.y)
		_hasChanged = true;

	_localPosition = newPos;
}

void TransformComponent::SetWorldScale(float scale)
{
	float newScale;
	if (_parent != nullptr)
		newScale = (_parent->GetWorldScale() + scale) / 2;
	else
		newScale = scale;

	if (newScale != _localScale)
		_hasChanged = true;

	_localScale = newScale;
}

void TransformComponent::SetWorldRotation(float rot)
{
	float newRot;
	if (_parent != nullptr)
		newRot = rot - _parent->GetWorldRotation();
	else
		newRot = rot;

	if (newRot != _localRotation)
		_hasChanged = true;

	_localRotation = newRot;
}

float TransformComponent::GetWorldRotation() const
{
	if (_parent != nullptr)
		return _localRotation + _parent->GetWorldRotation();
	else
		return _localRotation;
}

float TransformComponent::GetWorldScale() const
{
	if (_parent != nullptr)
		return _localScale * _parent->GetWorldScale();
	else
		return _localScale;
}

Vec2 TransformComponent::GetWorldPosition() const
{
	if (_parent != nullptr)
		return _localPosition + _parent->GetWorldPosition();
	else
		return _localPosition;
}

TransformComponent * ComponentFactory::MakeTransformComponent(Vec2 position, float rotation, float scale)
{
	TransformComponent * transform = new TransformComponent(position, rotation, scale);

	return transform;
}
