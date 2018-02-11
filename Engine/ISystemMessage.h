#pragma once

#include "Consts.h"

#include "IMessage.h"

class ISystemMessage : public IMessage
{
public:
	ISystemMessage(SystemMessageType messageType) : Type(messageType) { }

	SystemMessageType			Type;
};