#pragma once

#include "ISystemMessage.h"

class HWNDKey;

class InitaliseGraphicsMessage : public ISystemMessage
{
public:
	InitaliseGraphicsMessage(HWNDKey& key) : ISystemMessage(SystemMessageType::eGraphicsInitalise), Key(key) { }

	HWNDKey& Key;
};