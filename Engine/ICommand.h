#pragma once

#include "ISystemToGameObjectMessage.h"

class ICommand
{
public:
	virtual ~ICommand() {};
	virtual ISystemToGameObjectMessage Execute(/*player instance? Message to game loop?*/) = 0;
};

