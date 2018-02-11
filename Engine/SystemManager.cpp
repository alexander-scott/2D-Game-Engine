#include "SystemManager.h"

SystemManager::~SystemManager()
{
	for (auto s : _systems)
	{
		s.second = nullptr;
	}
}

void SystemManager::InitaliseMainWindow(HINSTANCE hInst, wchar_t * pArgs)
{
	_mainWindow = make_shared<MainWindow>(hInst, pArgs);
	_systems.insert(std::make_pair(_mainWindow->SysType, _mainWindow));
}

bool SystemManager::UpdateMainWindow()
{
	return _mainWindow->ProcessMessage();
}

void SystemManager::InitaliseSystems()
{
	// Initalise systems
	auto sceneBuilder = make_shared<SceneBuilder>();
	_systems.insert(std::make_pair(sceneBuilder->SysType, sceneBuilder));

	auto sceneManager = make_shared<SceneManager>();
	_systems.insert(std::make_pair(sceneManager->SysType, sceneManager));

	auto graphics = make_shared<TestGraphics>(); // Create a test graphics instance for now
	_systems.insert(std::make_pair(graphics->SysType, graphics));

	auto engine = make_shared<Engine>(); // Create engine last
	_systems.insert(std::make_pair(engine->SysType, engine));
}

std::shared_ptr<ISystem> SystemManager::GetSystem(SystemType type)
{
	if (_systems[type] == nullptr)
		throw std::exception("SYSTEM NOT INITALISED");

	return _systems[type];
}

void SystemManager::AddSystem(shared_ptr<ISystem> system, SystemType type)
{
	if (system == nullptr)
		throw std::exception("SYSTEM NOT INITALISED");

	_systems[type] = system;
}
