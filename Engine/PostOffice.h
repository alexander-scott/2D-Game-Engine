#pragma once

#include "IListener.h"
#include "IMessenger.h"

/* USAGE INSTRUCTIONS FOR POSTOFFICE SINGLETON

To register a class to recieve a type of message, call AddListener(). The calling class must inherit PostOfficeListener and the second parameter
is the type of message you want this class to recieve (add type as enum in Consts.h). The calling class must also override RecieveMessage()
as this is where the message will go to.

To send a message call SendMessageToListeners() and all classes that registered themselves with AddListener and the type of the message sent
will recieve the message. 

*/

class PostOffice
{
public:
	PostOffice();
	~PostOffice();

	// Adding a listener with a specific SystemMessageType means that any time a Message of that type gets sent through the PostOffice,
	// it will be sent to all Listeners added with that SystemMessageType.
	void AddListener(IListener* listener, SystemMessageType messageType);
	void RemoveListener(IListener* listener, SystemMessageType messageType);
	// Send a message to all Listeners that have been added to the PostOffice's registry with this messages SystemMessageType
	void SendMessageToListeners(ISystemMessage& message);

	static PostOffice& Instance()
	{
		static PostOffice Instance;
		return Instance;
	}

private:
	// Holds a map of MessageTypes, with each method type having numerous Listeners listening for a message being sent of that type
	std::map<SystemMessageType, std::vector<IListener*>>	_listeners;
};

