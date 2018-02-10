#include "PostOffice.h"

PostOffice::PostOffice()
{

}

PostOffice::~PostOffice()
{
}

void PostOffice::AddListener(IListener * listener, MessageType messageType)
{
	_listeners[messageType].push_back(listener);
}

void PostOffice::RemoveListener(IListener * listener, MessageType messageType)
{
	_listeners[messageType].erase(std::remove(_listeners[messageType].begin(), _listeners[messageType].end(), listener), _listeners[messageType].end());
}

void PostOffice::SendMessageToListeners(IMessage & message)
{
	for (int i = 0; i < _listeners[message.Type].size(); i++)
	{
		_listeners[message.Type][i]->RecieveMessage(message);
	}
}
