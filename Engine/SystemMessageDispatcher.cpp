#include "SystemMessageDispatcher.h"

void SystemMessageDispatcher::AddListener(IListener * listener, SystemMessageType messageType)
{
	_listeners[messageType].push_back(listener);
}

void SystemMessageDispatcher::RemoveListener(IListener * listener, SystemMessageType messageType)
{
	_listeners[messageType].erase(std::remove(_listeners[messageType].begin(), _listeners[messageType].end(), listener), _listeners[messageType].end());
}

void SystemMessageDispatcher::SendMessageToListeners(ISystemMessage & message)
{
	for (int i = 0; i < _listeners[message.Type].size(); i++)
	{
		_listeners[message.Type][i]->RecieveMessage(message);
	}
}