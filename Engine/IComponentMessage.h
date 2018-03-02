#pragma once

#include "Consts.h"

#include "IMessage.h"

class IComponentMessage : public IMessage
{
public:
	IComponentMessage(ComponentMessageType messageType) : MessageType(messageType) { }

	ComponentMessageType		MessageType;
};