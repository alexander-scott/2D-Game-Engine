#pragma once

#include "IMessage.h"

class RequestBuildScene : public IMessage
{
public:
	RequestBuildScene() : IMessage(MessageType::eRequestBuildSceneMessage) { }
};