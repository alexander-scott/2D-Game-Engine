#include "SystemManager.h"

SystemManager::SystemManager()
{
	auto sceneBuilder = make_shared<SceneBuilder>();
	_systems.insert(std::make_pair(sceneBuilder->SysType, sceneBuilder));

	auto graphics = make_shared<TestGraphics>(); // Create a test graphics instance for now
	_systems.insert(std::make_pair(graphics->SysType, graphics));
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
