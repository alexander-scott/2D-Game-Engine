#pragma once

#include "IListener.h"
#include "PostOffice.h"

class PostOfficeListener : public IListener
{
public:
	void SubscribeToMessageType(MessageType messageType)
	{
		PostOffice::Instance().AddListener(this, messageType);
	}
};