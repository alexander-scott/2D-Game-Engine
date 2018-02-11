#pragma once

#include "IComponentMessage.h"

class TransformComponent;

class SetParentTransformMessage : public IComponentMessage
{
public:
	SetParentTransformMessage(TransformComponent* parentTransform) : IComponentMessage(ComponentType::eTransformComponent)
	{
		ParentTransform = parentTransform;
	}

	TransformComponent*			ParentTransform;
};