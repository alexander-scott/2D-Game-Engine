#pragma once
#include "IDrawableComponent.h"

class SpriteRendererComponent : public IDrawableComponent 
{
public:
	SpriteRendererComponent();
	~SpriteRendererComponent();
	void Draw() override; //adds drawing data of this component to the message passed to the draw function
};

