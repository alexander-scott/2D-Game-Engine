#pragma once

#include "ISystemMessage.h"

class InputMouseMessage : public ISystemMessage
{
public:
	InputMouseMessage(MouseMessageType messageType, int xPos, int yPos) 
		: ISystemMessage(SystemMessageType::eInputMouseMessage)
	{
		MessageType = messageType;
		XPos = xPos;
		YPos = yPos;
	}

	MouseMessageType			MessageType;
	int							XPos;
	int							YPos;
};