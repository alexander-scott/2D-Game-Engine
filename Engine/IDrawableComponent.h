#pragma once

#include "Consts.h"

class IDrawableComponent
{
public:
	DrawableComponentType	Type;
	int						RenderLayer;

	virtual void Draw(float deltaTime) = 0; 
};