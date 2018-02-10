#pragma once

#include "IComponentMessage.h"

class IMessageable
{
public:
	virtual void RecieveMessage(IComponentMessage& message) = 0;
};