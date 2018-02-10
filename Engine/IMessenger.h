#pragma once

#include "IListener.h"
#include "ISystemMessage.h"

#include <vector>

class IMessenger
{
public:
	IMessenger(MessengerType type) : Type(type) { }

	void Subscribe(IListener* listener)
	{
		_listeners.push_back(listener);
	}

	void Unsubscribe(IListener* listener)
	{
		_listeners.erase(std::remove(_listeners.begin(), _listeners.end(), listener), _listeners.end());
	}

	void SendMessage(ISystemMessage& message)
	{
		for (int i = 0; i < _listeners.size(); i++)
		{
			_listeners[i]->RecieveMessage(message);
		}
	}

	MessengerType				Type;

private:
	std::vector<IListener*>		_listeners;
};