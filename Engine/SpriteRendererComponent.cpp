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

Vec2 SpriteRendererComponent::GetPosition()
{
	float halfSpriteWidth = (std::abs(_rect->right - _rect->left) / 2) * _transformComponent->GetWorldScale();
	float halfSpriteHeight = (std::abs(_rect->bottom - _rect->top) / 2) * _transformComponent->GetWorldScale();

	Vec2 pos = _transformComponent->GetWorldPosition();
	float newPosX = pos.x
		- halfSpriteWidth * cos(_transformComponent->GetWorldRotation())
		+ halfSpriteHeight * sin(_transformComponent->GetWorldRotation());

	float newPosY = pos.y
		- halfSpriteHeight * cos(_transformComponent->GetWorldRotation())
		+ halfSpriteWidth * sin(_transformComponent->GetWorldRotation());

	return Vec2(newPosX, newPosY);
}
