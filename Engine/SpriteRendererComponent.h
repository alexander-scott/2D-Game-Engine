#pragma once
#include "IRenderableComponent.h"
#include "ISpriteComponent.h"

class SpriteRendererComponent : /*public IRenderableComponent,*/ public ISpriteComponent, public IComponent
{
public:
	SpriteRendererComponent();
	SpriteRendererComponent(RECT *rect, Vec2 offset, string text, string name);

	~SpriteRendererComponent();

	//void SetDependencies(TransformComponent* transform);

	void Draw(float deltaTime) override; //adds drawing data of this component to the message passed to the draw function
	
	//getters & setters for scene informations
	//void SetName(std::string name);
	//std::string GetName();
	//std::string GetText();
	//std::string GetAnimation(); //TODO : delete


protected:

	//std::string _name;
	//std::string _text;
	////std::string _animation;
};

