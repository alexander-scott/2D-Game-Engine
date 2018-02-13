#pragma once

#include "DrawSceneMessage.h"

class IDrawableComponent
{
public:
	// Draw function must be overriden. Add sprite data to the message
	virtual void Draw(DrawSceneMessage& message) = 0;

	int			RenderLayer;
};