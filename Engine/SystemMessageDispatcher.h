#pragma once

#include "IListener.h"
#include "IMessenger.h"

/* USAGE INSTRUCTIONS FOR SYSTEM MESSAGE DISPATCHER SINGLETON

To register a class to recieve a type of message, call AddListener(). The calling class must inherit SystemMessageListener and the second parameter
is the type of message you want this class to recieve (SystemMessageType enum in Consts.h). The calling class must also override RecieveMessage()
as this is where the message will go to.

To send a message call SendMessageToListeners() through the singleton and all classes that registered themselves with AddListener and the type of 
the message sent will recieve the message. 

*/

class SystemMessageDispatcher
{
public:
	// Adding a listener with a specific SystemMessageType means that any time a Message of that type gets sent through the SystemMessageDispatcher,
	// it will be sent to all Listeners added with that SystemMessageType.
	void AddListener(IListener* listener, SystemMessageType messageType);
	void RemoveListener(IListener* listener, SystemMessageType messageType);
	// Send a message to all Listeners that have been added to the SystemMessageDispatcher's registry with this messages SystemMessageType
	void SendMessageToListeners(ISystemMessage& message);

protected:
	// Holds a map of MessageTypes, with each message type having numerous Listeners listening for a message being sent of that type
	std::map<SystemMessageType, std::vector<IListener*>>	_listeners;
};