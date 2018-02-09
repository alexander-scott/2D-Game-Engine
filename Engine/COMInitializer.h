#pragma once

#include "WinDefines.h"

class COMInitializer
{
public:
	COMInitializer();
	~COMInitializer();

private:
	HRESULT hr;
};