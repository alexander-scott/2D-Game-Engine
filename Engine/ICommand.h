#pragma once

#include "ISystemToGameObjectMessage.h"

class ICommand
{
protected:
	std::string _name;
public:
	virtual ~ICommand() {};
	virtual ISystemToGameObjectMessage Execute(/*player instance? Message to game loop?*/) = 0;
	std::string GetName() { return _name; };
};

