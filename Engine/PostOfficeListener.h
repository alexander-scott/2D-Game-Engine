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
};