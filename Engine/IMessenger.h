#pragma once

#include "IListener.h"
#include "ISystemMessage.h"

class IMessenger
{
public:
	void Subscribe(IListener* listener)
	{
		_listeners.push_back(listener);
	}

	void Unsubscribe(IListener* listener)
	{
		_listeners.erase(std::remove(_listeners.begin(), _listeners.end(), listener), _listeners.end());
	}

	void SendMessageToListeners(IMessage& message)
	{
		for (int i = 0; i < _listeners.size(); i++)
		{
			_listeners[i]->RecieveMessage(message);
		}
	}

private:
	std::vector<IListener*>		_listeners;
};