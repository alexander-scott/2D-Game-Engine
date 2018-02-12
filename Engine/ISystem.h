#pragma once

#include "Consts.h"

#include "SystemMessageListener.h"

class ISystem : public SystemMessageListener
{
public:
	ISystem(SystemType sysType) : SysType(sysType) { }

	virtual void InitaliseListeners() = 0;
	virtual void SystemsInitalised() { }

	SystemType	SysType;
};