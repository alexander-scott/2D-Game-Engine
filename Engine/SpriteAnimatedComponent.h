#pragma once
#include "IRenderableComponent.h"
#include "ISpriteComponent.h"

class SpriteAnimatedComponent : public ISpriteComponent, public IComponent
{
public:
	SpriteAnimatedComponent();
	SpriteAnimatedComponent(RECT *rect, Vec2 offset, string text, string name, string animation);

	~SpriteAnimatedComponent();

	void Draw(float deltaTime) override;

	std::string GetAnimation(); 

private:
	std::string _animation;
};

