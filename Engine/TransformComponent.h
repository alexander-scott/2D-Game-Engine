#pragma once

#include "IComponent.h"

#include "IEditableComponent.h"

class TransformComponent : public IComponent, public IEditableComponent
{
public:
	TransformComponent(Vec2 worldPosition, float worldRotation, float worldScale);
	~TransformComponent();
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

	bool CheckChanged();
	void SetChanged(bool changed) { _hasChanged = changed; }

	void SetParent(TransformComponent* parent) { _parent = parent; }

	// Editable Component
	virtual int GetEditorFieldCount() override;
	virtual InspectorField* GetEditorFields() override;
	virtual void SetEditorFieldValue(int fieldIndex, const char* value) override;

private:
	Vec2					_localPosition;
	float					_localRotation; // RADIANS
	float					_localScale;

	bool					_hasChanged;

	TransformComponent*		_parent;
};