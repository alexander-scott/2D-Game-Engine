#pragma once

#include "SystemMessageListener.h"

class ISystem : public SystemMessageListener
{
public:
	ISystem(SystemType sysType, std::shared_ptr<SystemMessageDispatcher> dispatcher) 
		: SysType(sysType), SystemMessageListener(dispatcher) { }

	virtual void InitaliseListeners() = 0;
	virtual void SystemsInitalised() { }

	SystemType	SysType;
};