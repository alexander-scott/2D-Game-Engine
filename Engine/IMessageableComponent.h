#pragma once

#include "IComponentMessage.h"

#include "IListener.h"

class IMessageableComponent : public IListener
{
public:
	virtual void RecieveMessage(IComponentMessage& message) = 0;

	virtual void RecieveMessage(IMessage& message) override
	{
		RecieveMessage(static_cast<IComponentMessage&>(message));
	}
};