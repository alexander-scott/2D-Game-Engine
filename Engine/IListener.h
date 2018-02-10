#pragma once

#include "ISystemMessage.h"

#include "Consts.h"

class IListener
{
public:
	virtual void RecieveMessage(ISystemMessage& message) = 0;
};