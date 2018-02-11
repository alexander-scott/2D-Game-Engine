#pragma once

#include "PostOffice.h"

class IDrawableComponent
{
public:
	// Draw function must be overriden
	virtual void Draw() = 0;

	int			RenderLayer;
};