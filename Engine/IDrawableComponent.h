#pragma once

#include "DrawSceneMessage.h"

class IDrawableComponent
{
public:
	DrawableComponentType	Type;
	int						RenderLayer;

	virtual void Draw() = 0; //Or Draw(FrameTimer)?
};