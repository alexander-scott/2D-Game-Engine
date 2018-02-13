#pragma once

#include "IMessenger.h"
#include "SystemMessageDispatcher.h"

// BROKEN
class SystemMessageMessenger : public IMessenger
{
public:
	SystemMessageMessenger(std::shared_ptr<SystemMessageDispatcher> dispatcher) 
		: SMDispatcher(dispatcher) { }

	void SendMessageToDispatcher(ISystemMessage& message)
	{
		SMDispatcher->SendMessageToListeners(message);
	}

private:
	std::shared_ptr<SystemMessageDispatcher> SMDispatcher;
};