#pragma once

#include "IComponent.h"

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

	bool CheckChanged() { return _hasChanged; }
	void SetChanged(bool changed) { _hasChanged = changed; }

	void SetParent(TransformComponent* parent) { _parent = parent; }

	virtual map<string, string> ExtractComponent() override;

	virtual IComponent* BuildComponent(xml_node<>* node) override;
	virtual xml_node<>* SaveComponent(xml_document<>* doc) override;
	virtual int GetEditorFieldCount() override;
	virtual InspectorField* GetEditorFields() override;

private:
	Vec2					_localPosition;
	float					_localRotation; // RADIANS
	float					_localScale;

	bool					_hasChanged;

	TransformComponent*		_parent;
};

namespace ComponentFactory
{
	TransformComponent * MakeTransformComponent(Vec2 position, float rotation, float scale);
}