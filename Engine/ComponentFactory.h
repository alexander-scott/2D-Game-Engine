#pragma once

#include "TransformComponent.h"

namespace ComponentFactory
{
	TransformComponent * MakeTransformComponent(Vec2 position, float rotation, float scale);
}