#pragma once

#include "IListener.h"
#include "SystemMessageDispatcher.h"

class SystemMessageListener : public IListener
{
public:
	SystemMessageListener(std::shared_ptr<SystemMessageDispatcher> dispatcher)
		: SMDispatcher(dispatcher) { }

	void SubscribeToMessageType(SystemMessageType messageType)
	{
		SMDispatcher->AddListener(this, messageType);
	}

	virtual void RecieveMessage(ISystemMessage& message) = 0;

	virtual void RecieveMessage(IMessage& message) override
	{
		RecieveMessage(static_cast<ISystemMessage&>(message));
	}

private:
	std::shared_ptr<SystemMessageDispatcher> SMDispatcher;
};