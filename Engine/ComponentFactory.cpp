#include "ComponentFactory.h"

TransformComponent * ComponentFactory::MakeTransformComponent(Vec2 position, float rotation, float scale)
{
	TransformComponent * transform = new TransformComponent(position, rotation, scale);

	return transform;
}