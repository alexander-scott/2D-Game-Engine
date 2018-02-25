#include "SystemManager.h"

#include "Engine.h"
#include "SceneBuilder.h"
#include "SceneManager.h"
#include "TestGraphics.h"
#include "InputHandler.h"
#include "Editor.h"

#include "RequestBuildSceneMessage.h"

SystemManager::SystemManager(HWND hWnd)
{
	_messageDispatcher = make_shared<SystemMessageDispatcher>();

	// Initalise MainWindow system
	_mainWindow = make_shared<MainWindow>(hWnd, _messageDispatcher);
	_systems.insert(std::make_pair(_mainWindow->SysType,_mainWindow));

	InitaliseSystems();
	InitaliseListeners();
	SystemsInitalised();

	// Initalise the Editor system
	auto editorSystem = make_shared<Editor>(_messageDispatcher);
	_systems.insert(std::make_pair(editorSystem->SysType, editorSystem));
}

SystemManager::SystemManager(HINSTANCE hInst, wchar_t * pArgs)
{
	_messageDispatcher = make_shared<SystemMessageDispatcher>();

	// Initalise MainWindow system
	_mainWindow = make_shared<MainWindow>(hInst, pArgs, _messageDispatcher);
	_systems.insert(std::make_pair(_mainWindow->SysType, _mainWindow));

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
		s.second = nullptr;
	}
}

void SystemManager::StartUpdateLoop()
{
	bool result = true;
	do 
	{
		_messageDispatcher->SendMessageToListeners(ISystemMessage(SystemMessageType::eSystemUpdate));

		if (_mainWindow != nullptr)
			result = _mainWindow->ProcessMessage();
		else
			result = true;
	} 
	while (result);
}

// Create an instance of every system. Can be initalised in any order. Inject instance of message dispatcher.
void SystemManager::InitaliseSystems()
{
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

	// Initalise Input Handler System
	auto inputHandler = make_shared<InputHandler>(_messageDispatcher);
	_systems.insert(std::make_pair(inputHandler->SysType, inputHandler));
}

// If any of the systems are listening for message this function sets it up. Called after system initalisation.
void SystemManager::InitaliseListeners()
{
	for (auto s : _systems)
	{
		s.second->InitaliseListeners();
	}
}

// This is a simple callback for each system after every system has been intialised with listeners
void SystemManager::SystemsInitalised()
{
	for (auto s : _systems)
	{
		s.second->SystemsInitalised();
	}
}