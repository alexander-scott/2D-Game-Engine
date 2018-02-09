#pragma once

#include "Consts.h"

class IMessage
{
public:
	IMessage(MessageType messageType) : Type(messageType) { }

	MessageType			Type;
};