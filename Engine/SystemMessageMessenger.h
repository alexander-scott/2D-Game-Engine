#pragma once

#include "IMessenger.h"
#include "SystemMessageDispatcher.h"

class SystemMessageMessenger : public IMessenger
{
public:
	SystemMessageMessenger(std::shared_ptr<SystemMessageDispatcher> dispatcher) 
		: _systemMessageDispatcher(dispatcher) { }

	void SendMessageToDispatcher(ISystemMessage& message)
	{
		_systemMessageDispatcher->SendMessageToListeners(message);
	}

private:
	std::shared_ptr<SystemMessageDispatcher> _systemMessageDispatcher;
};