#pragma once

#include "Consts.h"

class ISystem
{
public:
	ISystem(SystemType sysType) : SysType(sysType) { }

	SystemType	SysType;
};