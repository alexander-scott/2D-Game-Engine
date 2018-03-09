#pragma once

#include "ISystemMessage.h"

class RequestSaveSceneMessage : public ISystemMessage
{
public:
	RequestSaveSceneMessage(std::string filePath) : ISystemMessage(SystemMessageType::eRequestSaveSceneMessage)
	{
		FilePath = filePath;
	}

	std::string			FilePath;
};