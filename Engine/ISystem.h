#pragma once

#include "Consts.h"

#include "PostOfficeListener.h"

class ISystem : public PostOfficeListener
{
public:
	ISystem(SystemType sysType) : SysType(sysType) { }

	SystemType	SysType;
};