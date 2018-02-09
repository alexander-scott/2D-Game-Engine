#pragma once

#include "IListener.h"
#include "PostOffice.h"

class PostOfficeListener : public IListener
{
public:
	void Subscribe(MessengerType messengerType)
	{
		PostOffice::Instance().GetMessenger(messengerType)->Subscribe(this);
	}

	void Subscribe(MessageType messageType)
	{
		PostOffice::Instance().AddListener(this, messageType);
	}
};