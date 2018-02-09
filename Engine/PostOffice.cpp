#include "PostOffice.h"

PostOffice::PostOffice()
{

}

PostOffice::~PostOffice()
{
}

void PostOffice::InitaliseMessenger(IMessenger * messenger)
{
	if (messenger == nullptr)
		throw std::exception("MESSENGER NOT INITALISED");

	_messengers[messenger->Type] = messenger;
}

IMessenger * PostOffice::GetMessenger(MessengerType messengerType)
{
	if (_messengers[messengerType] == nullptr)
		throw std::exception("MESSENGER NOT INITALISED");

	return _messengers[messengerType];
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
