#pragma once

#include "SystemMessageListener.h"
#include "SystemMessageMessenger.h"

class ISystem : public SystemMessageListener, public SystemMessageMessenger
{
public:
	ISystem(SystemType sysType, std::shared_ptr<SystemMessageDispatcher> dispatcher) 
		: SysType(sysType), SystemMessageListener(dispatcher), SystemMessageMessenger(dispatcher) { }

	virtual void InitaliseListeners() = 0;
	virtual void SystemsInitalised() { }

	SystemType	SysType;
};