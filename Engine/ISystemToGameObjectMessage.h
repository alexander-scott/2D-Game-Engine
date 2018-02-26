#pragma once

#include "ISystemMessage.h"

#include "IComponentMessage.h"

class ISystemToGameObjectMessage : public ISystemMessage
{
public:
	ISystemToGameObjectMessage(IComponentMessage& message) 
		: ISystemMessage(SystemMessageType::eSendMessageToGameObjects), Message(message)
	{

	}

	IComponentMessage&		Message;
};