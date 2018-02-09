#pragma once

#include "IMessenger.h"
#include "PostOffice.h"

class PostOfficeMessenger : public IMessenger
{
public:
	PostOfficeMessenger(MessengerType messengerType) : IMessenger(messengerType)
	{
		PostOffice::Instance().InitaliseMessenger(this);
	}
};