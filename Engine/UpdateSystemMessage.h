#pragma once

#include "ISystemMessage.h"

class UpdateSystemMessage : public ISystemMessage
{
public:
	UpdateSystemMessage(SystemMessageType systemType, float deltaTime) : ISystemMessage(systemType)
	{
		DeltaTime = deltaTime;
	}	

	float DeltaTime;
};