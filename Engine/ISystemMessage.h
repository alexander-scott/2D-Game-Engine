#pragma once

#include "Consts.h"

class ISystemMessage
{
public:
	ISystemMessage(SystemMessageType messageType) : Type(messageType) { }

	SystemMessageType			Type;
};