#pragma once

#include "Consts.h"

#include "ISystem.h"

#include "SceneBuilder.h"
#include "TestGraphics.h"

class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	std::shared_ptr<ISystem> GetSystem(SystemType type);

private:
	std::map<SystemType, std::shared_ptr<ISystem>>		_systems;
};