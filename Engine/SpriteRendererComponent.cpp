#include "SpriteRendererComponent.h"



SpriteRendererComponent::SpriteRendererComponent()
{
}

SpriteRendererComponent::SpriteRendererComponent(Vec2 position, float rotation, float scale, RECT *rect, Vec2 offset, string name)
{
	SetPosition(position);
	SetRotation(rotation);
	SetScale(scale);
	SetRect(rect);
	SetOffset(offset);
	_name = name;
}


SpriteRendererComponent::~SpriteRendererComponent()
{
}


//Draw : passes data to the message sent to draw function in Graphics System
void SpriteRendererComponent::Draw(float deltaTime)
{
	//TODO
}

void SpriteRendererComponent::SetName(std::string name)
{
	_name = name;
}

std::string SpriteRendererComponent::GetName()
{
	return _name;
}
