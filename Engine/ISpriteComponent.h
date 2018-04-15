#pragma once
#include "IRenderableComponent.h"

class ISpriteComponent : public IRenderableComponent
{
public:
	ISpriteComponent();
	ISpriteComponent(RECT *rect, Vec2 offset, string text, string name);
	~ISpriteComponent();

	void SetDependencies(TransformComponent* transform);

	void SetName(std::string name);
	std::string GetName();
	std::string GetText();


protected:

	std::string _name;
	std::string _text;
};

