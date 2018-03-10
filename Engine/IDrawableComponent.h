#pragma once

#include "Consts.h"

class IDrawableComponent
{
public:
	DrawableComponentType	Type;
	int						RenderLayer;
};