#pragma once
#include "IDrawableComponent.h"
#include "TransformComponent.h"

class IRenderableComponent : public IDrawableComponent
{
public:
	//getters 
	virtual Vec2 GetPosition() { return _transformComponent->GetWorldPosition();};
	virtual RECT* GetRect() { return _rect; };
	virtual float GetRotation() { return _transformComponent->GetWorldRotation(); };
	virtual float GetScale() { return _transformComponent->GetWorldScale(); };
	virtual Vec2 GetOffset() { return _offset; };

	//setters
	virtual void SetRect(RECT* rect) {_rect = rect;};
	virtual void SetOffset(Vec2 offset) { _offset = offset; };
	virtual void SetPosition(Vec2 position) { _transformComponent->SetWorldPosition(position); }
	virtual void SetScale(float scale) { _transformComponent->SetWorldScale(scale); }
	virtual void SetRotation(float rotation) { _transformComponent->SetWorldRotation(rotation); }

protected:
	//informations needed to draw the component from the scene file
	//Would shared_ptr be better for these attributes?
	//TODO : delete and retrieve from transform component (add pointer transform comp)
	TransformComponent *_transformComponent = nullptr; 
	RECT * _rect;
	Vec2 _offset;


};