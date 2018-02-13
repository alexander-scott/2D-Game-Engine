#include "SystemManager.h"

#include "Engine.h"
#include "SceneBuilder.h"
#include "SceneManager.h"
#include "TestGraphics.h"

SystemManager::SystemManager(HINSTANCE hInst, wchar_t * pArgs)
{
	_messageDispatcher = make_shared<SystemMessageDispatcher>();

	InitaliseSystems(hInst, pArgs);
	InitaliseListeners();
	SystemsInitalised();
}

SystemManager::~SystemManager()
{
	for (auto s : _systems)
	{
		s.second = nullptr;
	}
}

bool SystemManager::SystemUpdate()
{
	_messageDispatcher->SendMessageToListeners(ISystemMessage(SystemMessageType::eSystemUpdate));

	if (_mainWindow != nullptr)
		return _mainWindow->ProcessMessage();
	else
		return true;
}

// Create an instance of every system. Can be initalised in any order. Inject instance of message dispatcher.
void SystemManager::InitaliseSystems(HINSTANCE hInst, wchar_t * pArgs)
{
	// Initalise MainWindow system
	_mainWindow = make_shared<MainWindow>(hInst, pArgs, _messageDispatcher);
	_systems.insert(std::make_pair(_mainWindow->SysType, _mainWindow));

	// Initalise SceneBuilder system
	auto sceneBuilder = make_shared<SceneBuilder>(_messageDispatcher);
	_systems.insert(std::make_pair(sceneBuilder->SysType, sceneBuilder));

	// Initalise SceneManager system
	auto sceneManager = make_shared<SceneManager>(_messageDispatcher);
	_systems.insert(std::make_pair(sceneManager->SysType, sceneManager));

	// Initalise Graphics system
	auto graphics = make_shared<TestGraphics>(_messageDispatcher); // Create a test graphics instance for now
	_systems.insert(std::make_pair(graphics->SysType, graphics));

	// Initalise Engine system
	auto engine = make_shared<Engine>(_messageDispatcher);
	_systems.insert(std::make_pair(engine->SysType, engine));
}

// If any of the systems are listening for message this function sets it up. Called after system initalisation.
void SystemManager::InitaliseListeners()
{
	map<SystemType, std::shared_ptr<ISystem>>::iterator system;

	for (system = _systems.begin(); system != _systems.end(); system++)
	{
		system->second->InitaliseListeners();
	}
}

// This is a simple callback for each system after every system has been intialised with listeners
void SystemManager::SystemsInitalised()
{
	map<SystemType, std::shared_ptr<ISystem>>::iterator system;

	for (system = _systems.begin(); system != _systems.end(); system++)
	{
		system->second->SystemsInitalised();
	}
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
