#pragma once

#include "Consts.h"

class IComponentMessage
{
public:
	IComponentMessage(ComponentType componentType) : ComponentRecipient(componentType) { }

	ComponentType			ComponentRecipient;
};