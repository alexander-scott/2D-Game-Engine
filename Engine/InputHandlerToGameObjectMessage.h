#pragma once

#include "ISystemMessage.h"

class InputHandlerToGameObjectMessage : public ISystemMessage
{
public:
	InputHandlerToGameObjectMessage(InputGenericStateMessageType messageType, sCommand command, float range)
		: ISystemMessage(SystemMessageType::eInputHandlerToGameObjectMessage)
	{
		MessageType = messageType;
		Command = command;
		Range = range /*-1 : no range senstivity applied, for example if key pressed comes from a button*/;
	}

	InputGenericStateMessageType MessageType;
	sCommand Command;
	float Range;
};
