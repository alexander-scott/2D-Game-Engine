#include "SpriteRendererComponent.h"



SpriteRendererComponent::SpriteRendererComponent()
{
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

void SpriteRendererComponent::SetPosition(Vec2 position)
{
	_position = position;
}

void SpriteRendererComponent::SetRect(RECT * rect)
{
	_rect = rect;
}

void SpriteRendererComponent::SetRotation(float rotation)
{
	_rotation = rotation;
}

void SpriteRendererComponent::SetScale(float scale)
{
	_scale = scale;
}

void SpriteRendererComponent::SetOffset(Vec2 offset)
{
	_offset = offset;
}

std::string SpriteRendererComponent::GetName()
{
	return _name;
}

Vec2 SpriteRendererComponent::GetPosition()
{
	return _position;
}

RECT * SpriteRendererComponent::GetRect()
{
	return _rect;
}


float SpriteRendererComponent::GetRotation()
{
	return _rotation;
}

float SpriteRendererComponent::GetScale()
{
	return _scale;
}

Vec2 SpriteRendererComponent::GetOffset()
{
	return Vec2();
}
