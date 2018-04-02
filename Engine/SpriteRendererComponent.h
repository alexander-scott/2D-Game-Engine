#pragma once
#include "IRenderableComponent.h"

class SpriteRendererComponent : public IRenderableComponent, public IComponent
{
public:
	SpriteRendererComponent();
	SpriteRendererComponent(Vec2 position, float rotation, float scale,  RECT *rect, Vec2 offset, string text, string name, string animation);
	~SpriteRendererComponent();
	void Draw(float deltaTime) override; //adds drawing data of this component to the message passed to the draw function
	
	//getters & setters for scene informations
	void SetName(std::string name);
	std::string GetName();
	std::string GetText();
	std::string GetAnimation();


private:

	std::string _name;
	std::string _text;
	std::string _animation;
};

