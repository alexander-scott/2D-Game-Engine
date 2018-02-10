#pragma once

#include "IComponent.h"
#include "Consts.h"

class TransformComponent : public IComponent
{
public:
	TransformComponent(Vec2 worldPosition, float worldRotation, float worldScale);

	void SetLocalPosition(Vec2 position);
	void SetLocalScale(float scale);
	void SetLocalRotation(float rot);

	float GetLocalRotation() const;
	float GetLocalScale() const;
	Vec2 GetLocalPosition() const;

	void SetWorldPosition(Vec2 position);
	void SetWorldScale(float scale);
	void SetWorldRotation(float rot);

	float GetWorldRotation() const;
	float GetWorldScale() const;
	Vec2 GetWorldPosition() const;

	bool CheckChanged() { return mHasChanged; }
	void SetChanged(bool changed) { mHasChanged = changed; }

	void SetParent(TransformComponent* parent) { mParent = parent; }

private:
	Vec2					mLocalPosition;
	float					mLocalRotation; // RADIANS
	float					mLocalScale;

	bool					mHasChanged;

	TransformComponent*		mParent;
};

namespace ComponentFactory
{
	TransformComponent * MakeTransformComponent(Vec2 position, float rotation, float scale);
}