#pragma once

#include "IMessage.h"

#include "Consts.h"

class IListener
{
public:
	virtual void RecieveMessage(IMessage& message) = 0;
};