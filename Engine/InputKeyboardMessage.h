#pragma once

#include "ISystemMessage.h"

class InputKeyboardMessage : public ISystemMessage
{
public:
	InputKeyboardMessage(KeyboardMessageType messageType, unsigned char key) 
		: ISystemMessage(SystemMessageType::eInputKeyboardMessage)
	{
		MessageType = messageType;
		Key = key;
	}

	KeyboardMessageType		MessageType;
	unsigned char			Key;
};