#pragma once

#include "ISystemMessage.h"

class RequestBuildSceneMessage : public ISystemMessage
{
public:
	RequestBuildSceneMessage(std::string filePath) : ISystemMessage(SystemMessageType::eRequestBuildSceneMessage)
	{
		FilePath = filePath;
	}

	std::string			FilePath;
};