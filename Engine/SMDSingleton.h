#pragma once

#include "SystemMessageDispatcher.h"

class SMDSingleton : public SystemMessageDispatcher
{
public:
	static SMDSingleton& Instance()
	{
		static SMDSingleton Instance;
		return Instance;
	}
};