#include "SystemManager.h"

#include "Engine.h"
#include "SceneBuilder.h"
#include "SceneManager.h"
#include "TestGraphics.h"
#include "InputHandler.h"

#include "RequestBuildSceneMessage.h"

SystemManager::SystemManager(HWND hWnd)
{
	_messageDispatcher = make_shared<SystemMessageDispatcher>();

	// Initalise MainWindow system
	_mainWindow = make_shared<MainWindow>(hWnd, _messageDispatcher);
	_systems.push_back(_mainWindow);

	InitaliseSystems();
	InitaliseListeners();
	SystemsInitalised();
}

SystemManager::SystemManager(HINSTANCE hInst, wchar_t * pArgs)
{
	_messageDispatcher = make_shared<SystemMessageDispatcher>();

	// Initalise MainWindow system
	_mainWindow = make_shared<MainWindow>(hInst, pArgs, _messageDispatcher);
	_systems.push_back(_mainWindow);

	InitaliseSystems();
	InitaliseListeners();
	SystemsInitalised();

	// Request a new scene be built by the SceneBuilder system
	RequestBuildSceneMessage message("..\\Resources\\Scenes\\Scene1.xml"); // Hardcoded for now
	_messageDispatcher->SendMessageToListeners(message);
}

SystemManager::~SystemManager()
{
	for (auto s : _systems)
	{
		s = nullptr;
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
void SystemManager::InitaliseSystems()
{
	// Initalise SceneBuilder system
	auto sceneBuilder = make_shared<SceneBuilder>(_messageDispatcher);
	_systems.push_back(sceneBuilder);

	// Initalise SceneManager system
	auto sceneManager = make_shared<SceneManager>(_messageDispatcher);
	_systems.push_back(sceneManager);

	// Initalise Graphics system
	auto graphics = make_shared<TestGraphics>(_messageDispatcher); // Create a test graphics instance for now
	_systems.push_back(graphics);

	// Initalise Engine system
	auto engine = make_shared<Engine>(_messageDispatcher);
	_systems.push_back(engine);

	// Initalise Input Handler System
	auto inputHandler = make_shared<InputHandler>(_messageDispatcher);
	_systems.push_back(inputHandler);
}

// If any of the systems are listening for message this function sets it up. Called after system initalisation.
void SystemManager::InitaliseListeners()
{
	for (auto s : _systems)
	{
		s->InitaliseListeners();
	}
}

// This is a simple callback for each system after every system has been intialised with listeners
void SystemManager::SystemsInitalised()
{
	for (auto s : _systems)
	{
		s->SystemsInitalised();
	}
}