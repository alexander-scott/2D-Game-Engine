#pragma once

#include "ISystemMessage.h"

class PlayAudioMessage : public ISystemMessage
{
public:
	PlayAudioMessage(std::string fileName) : ISystemMessage(SystemMessageType::ePlaySound)
	{
		FileName = fileName;
	}

	std::string FileName;
};