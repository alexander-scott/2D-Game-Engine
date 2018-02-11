#pragma once

#include "IListener.h"
#include "SystemMessageDispatcher.h"

class SystemMessageListener : public IListener
{
public:
	void SubscribeToMessageType(SystemMessageType messageType)
	{
		SystemMessageDispatcher::Instance().AddListener(this, messageType);
	}

	virtual void RecieveMessage(ISystemMessage& message) = 0;

	virtual void RecieveMessage(IMessage& message) override
	{
		RecieveMessage(static_cast<ISystemMessage&>(message));
	}
};