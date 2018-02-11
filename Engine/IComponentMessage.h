#pragma once

#include "Consts.h"

#include "IMessage.h"

class IComponentMessage : public IMessage
{
public:
	IComponentMessage(ComponentType componentType) : ComponentRecipient(componentType) { }

	ComponentType			ComponentRecipient;
};