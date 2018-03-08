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

std::string SpriteRendererComponent::GetName()
{
	return _name;
}
