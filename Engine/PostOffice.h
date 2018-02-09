#pragma once

#include "IListener.h"
#include "IMessenger.h"

class PostOffice
{
public:
	PostOffice();
	~PostOffice();

	void InitaliseMessenger(IMessenger* messenger);
	IMessenger* GetMessenger(MessengerType messengerType);

	// Adding a listener with a specific MessageType means that any time a Message of that type gets sent through the PostOffice,
	// it will be sent to all Listeners added with that MessageType.
	void AddListener(IListener* listener, MessageType messageType);
	void RemoveListener(IListener* listener, MessageType messageType);
	// Send a message to all Listeners that have been added to the PostOffice's registry with this messages MessageType
	void SendMessageToListeners(IMessage& message);

	static PostOffice& Instance()
	{
		static PostOffice Instance;
		return Instance;
	}

private:
	// Holds a map of Messengers with an ID
	std::map<MessengerType, IMessenger*>			_messengers;
	// Holds a map of MessageTypes, with each method type having numerous Listeners listening for a message being sent of that type
	std::map<MessageType, std::vector<IListener*>>	_listeners;
};

