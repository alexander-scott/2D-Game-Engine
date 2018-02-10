#include "SystemManager.h"

SystemManager::SystemManager()
{
	auto sceneBuilder = make_shared<SceneBuilder>();
	_systems.insert(std::make_pair(sceneBuilder->SysType, sceneBuilder));
}

SystemManager::~SystemManager()
{
	for (auto s : _systems)
	{
		s.second = nullptr;
	}
}

std::shared_ptr<ISystem> SystemManager::GetSystem(SystemType type)
{
	if (_systems[type] == nullptr)
		throw std::exception("SYSTEM NOT INITALISED");

	return _systems[type];
}
