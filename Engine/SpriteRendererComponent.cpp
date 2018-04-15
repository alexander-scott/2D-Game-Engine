#include "SpriteRendererComponent.h"


SpriteRendererComponent::SpriteRendererComponent() : IComponent("SpriteRendererComponent")
{
}

SpriteRendererComponent::SpriteRendererComponent(RECT *rect, Vec2 offset, string text, string name, string animation) : ISpriteComponent(rect, offset, text, name), IComponent("SpriteRendererComponent")
{
	Type = eSprite;
}

SpriteRendererComponent::~SpriteRendererComponent()
{
}


//Draw : passes data to the message sent to draw function in Graphics System
void SpriteRendererComponent::Draw(float deltaTime)
{
	//TODO - delete?
}
