#pragma once

#include "IComponentMessage.h"

class InputHandlerToGameObjectMessage : public IComponentMessage
{
public:
	InputHandlerToGameObjectMessage(InputGenericStateMessageType messageType, sCommand command, float range)
		: IComponentMessage(ComponentMessageType::eInputHandlerToGameObjectMessage)
	{
		MessageType = messageType;
		Command = command;
		Range = range /*-1 : no range senstivity applied, for example if key pressed comes from a button*/;
	}

	InputGenericStateMessageType MessageType;
	sCommand Command;
	float Range;
};
