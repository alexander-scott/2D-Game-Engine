#pragma once
#include "IDrawableComponent.h"

class IRenderableComponent : public IDrawableComponent
{
public:
	//getters 
	virtual Vec2 GetPosition() { return _position;};
	virtual RECT* GetRect() { return _rect; };
	virtual float GetRotation() { return _rotation; };
	virtual float GetScale() { return _scale; };
	virtual Vec2 GetOffset() { return _offset; };

	//setters
	virtual void SetPosition(Vec2 position) {_position = position;};
	virtual void SetPosition(float x, float y) {_position.x = x; _position.y = y;};
	virtual void SetRect(RECT* rect) {_rect = rect;};
	virtual void SetRotation(float rotation) {_rotation = rotation;};
	virtual void SetScale(float scale) { _scale = scale; };
	virtual void SetOffset(Vec2 offset) { _offset = offset; };

private:
	//informations needed to draw the component from the scene file
	//Would shared_ptr be better for these attributes?
	Vec2 _position;
	RECT * _rect;
	float _rotation;
	float _scale;
	Vec2 _offset;

};