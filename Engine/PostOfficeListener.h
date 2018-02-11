#pragma once

#include "IListener.h"
#include "PostOffice.h"

class PostOfficeListener : public IListener
{
public:
	void SubscribeToMessageType(SystemMessageType messageType)
	{
		PostOffice::Instance().AddListener(this, messageType);
	}

	virtual void RecieveMessage(ISystemMessage& message) = 0;

	virtual void RecieveMessage(IMessage& message) override
	{
		RecieveMessage(static_cast<ISystemMessage&>(message));
	}
};