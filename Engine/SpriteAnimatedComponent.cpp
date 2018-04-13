#include "SpriteAnimatedComponent.h"


SpriteAnimatedComponent::SpriteAnimatedComponent() :  IComponent("SpriteAnimatedComponent")
{
}

SpriteAnimatedComponent::SpriteAnimatedComponent(RECT *rect, Vec2 offset, string text, string name, string animation) : ISpriteComponent(rect, offset, text, name), IComponent("SpriteAnimatedComponent")
{
	Type = eSpriteAnimated;

	_animation = animation;
}

SpriteAnimatedComponent::~SpriteAnimatedComponent()
{
}

void SpriteAnimatedComponent::Draw(float deltaTime)
{
}


std::string SpriteAnimatedComponent::GetAnimation()
{
	return _animation;
}
