#pragma once

#include "DrawSceneMessage.h"

class IDrawableComponent
{
public:
	DrawableComponentType	Type;
	int						RenderLayer;
};