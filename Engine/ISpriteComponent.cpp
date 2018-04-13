#include "ISpriteComponent.h"



ISpriteComponent::ISpriteComponent()
{
}

ISpriteComponent::ISpriteComponent(RECT * rect, Vec2 offset, string text, string name)
{
	SetRect(rect);
	SetOffset(offset);
	_name = name;
	_text = text;
}


ISpriteComponent::~ISpriteComponent()
{
}

void ISpriteComponent::SetDependencies(TransformComponent * transform)
{
	_transformComponent = transform;
}

void ISpriteComponent::SetName(std::string name)
{
	_name = name;
}

std::string ISpriteComponent::GetName()
{
	return _name;
}

std::string ISpriteComponent::GetText()
{
	return _text;
}
