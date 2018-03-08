#pragma once
#include "IDrawableComponent.h"

class SpriteRendererComponent : public IDrawableComponent 
{
public:
	SpriteRendererComponent();
	~SpriteRendererComponent();
	void Draw(float deltaTime) override; //adds drawing data of this component to the message passed to the draw function
	
	//getters & setters for scene informations
	void SetName(std::string name);
	void SetPosition(Vec2 position);
	void SetRect(RECT* rect);
	void SetRotation(float rotation);
	void SetScale(float scale);
	void SetOffset(Vec2 offset);

	std::string GetName();
	Vec2 GetPosition();
	RECT* GetRect();
	float GetRotation();
	float GetScale();
	Vec2 GetOffset();

private:
	//informations needed to draw the component from the scene file
	//Would shared_ptr be better for these attributes?
	std::string _name;
	Vec2 _position;
	RECT * _rect;
	float _rotation; 
	float _scale;
	Vec2 _offset;
};

