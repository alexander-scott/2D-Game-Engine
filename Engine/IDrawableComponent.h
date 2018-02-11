#pragma once

#include "SystemMessageDispatcher.h"

class IDrawableComponent
{
public:
	// Draw function must be overriden
	virtual void Draw() = 0;

	int			RenderLayer;
};