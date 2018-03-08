#pragma once
#include "IRenderableComponent.h"

class SpriteRendererComponent : public IRenderableComponent
{
public:
	SpriteRendererComponent();
	~SpriteRendererComponent();
	void Draw(float deltaTime) override; //adds drawing data of this component to the message passed to the draw function
	
	//getters & setters for scene informations
	void SetName(std::string name);
	std::string GetName();

private:

	std::string _name;
};

