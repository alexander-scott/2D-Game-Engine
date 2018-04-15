#pragma once

#include <string>

class GlobalVariables
{
public:
	static GlobalVariables& Instance()
	{
		static GlobalVariables instance;
		return instance;
	}

	std::string ResourcesFilePath;
};