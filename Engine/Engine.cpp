#include "Engine.h"

#include "SceneBuilder.h"
#include "SceneManager.h"
#include "SceneSaver.h"
#include "TestGraphics.h"
#include "InputHandler.h"
#include "MainWindow.h"
#include "Editor.h"
#include "PhysicsSystem.h"

#include "RequestBuildSceneMessage.h"
#include "RequestSaveSceneMessage.h"

// Called from the editor
Engine::Engine(HWND hWnd)
{
	_messageDispatcher = make_shared<SystemMessageDispatcher>();

	Logger::Instance().LogMessage("Initalising the MainWindow system with a HWND", LogSeverity::eInfo);
	_mainWindow = make_shared<MainWindow>(hWnd, _messageDispatcher);
	_systems.insert(std::make_pair(_mainWindow->SysType,_mainWindow));

	_lastTime = std::chrono::steady_clock::now();
	_lag = 0;

	InitaliseSystems();

	Logger::Instance().LogMessage("Initalising the Editor system", LogSeverity::eInfo);
	auto editorSystem = make_shared<Editor>(_messageDispatcher);
	_systems.insert(std::make_pair(editorSystem->SysType, editorSystem));

	InitaliseListeners();
	SystemsInitalised();
}

// Called in the standalone engine
Engine::Engine(HINSTANCE hInst, wchar_t * pArgs)
{
	_messageDispatcher = make_shared<SystemMessageDispatcher>();

	Logger::Instance().LogMessage("Initalising the MainWindow system with a HINSTANCE", LogSeverity::eInfo);
	_mainWindow = make_shared<MainWindow>(hInst, pArgs, _messageDispatcher);
	_systems.insert(std::make_pair(_mainWindow->SysType, _mainWindow));

	_lastTime = std::chrono::steady_clock::now();
	_lag = 0;

	InitaliseSystems();
	InitaliseListeners();
	SystemsInitalised();

	Logger::Instance().LogMessage("Requesting a new scene be built by the SceneBuilder system", LogSeverity::eInfo);
	RequestBuildSceneMessage message("..\\Resources\\Scenes\\Scene1.xml"); // Hardcoded for now
	_messageDispatcher->SendMessageToListeners(message);

	Logger::Instance().LogMessage("Play mode starting", LogSeverity::eInfo);
	_messageDispatcher->SendMessageToListeners(ISystemMessage(SystemMessageType::ePlayStarted));

	// FOR TESTING
	//RequestSaveSceneMessage msg("..\\Resources\\Scenes\\Scene1.xml");
	//_messageDispatcher->SendMessageToListeners(msg);
}

Engine::~Engine()
{
	for (auto s : _systems)
	{
		s.second = nullptr;
	}
}

void Engine::StartUpdateLoop()
{
	bool result = true;
	do 
	{
		auto currentTime = std::chrono::steady_clock::now();
		const std::chrono::duration<float> elapsedTime = currentTime - _lastTime;
		_lastTime = currentTime;
		_lag += elapsedTime.count();

		_messageDispatcher->SendMessageToListeners(ISystemMessage(SystemMessageType::eInputUpdateGamePad));

		// This while loop processes scene updates and physics at a fixed rate.
		// Whilst allowing graphics to render as fast as possible.
		while (_lag >= MS_PER_UPDATE)
		{
			// ProcessPhysics()

			// Update the current scene in the SceneManager system
			_messageDispatcher->SendMessageToListeners(ISystemMessage(SystemMessageType::eUpdateScene));

			_lag -= MS_PER_UPDATE;
		}

		_messageDispatcher->SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsStartFrame)); // Tell the Graphics system to begin the frame

		_messageDispatcher->SendMessageToListeners(ISystemMessage(SystemMessageType::eDrawScene)); // Draw the current scene in the SceneManager system

		_messageDispatcher->SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsEndFrame)); // Tell the Graphics system to end the frame

		if (_mainWindow != nullptr)
			result = _mainWindow->ProcessMessage(); // Check if the user presses close on the window
		else
			result = true;
	} 
	while (result);
}

// Create an instance of every system. Can be initalised in any order. Inject instance of message dispatcher.
void Engine::InitaliseSystems()
{
	Logger::Instance().LogMessage("Initalising SceneBuilder system", LogSeverity::eInfo);
	auto sceneBuilder = make_shared<SceneBuilder>(_messageDispatcher);
	_systems.insert(std::make_pair(sceneBuilder->SysType, sceneBuilder));

	Logger::Instance().LogMessage("Initalising SceneManager system", LogSeverity::eInfo);
	auto sceneManager = make_shared<SceneManager>(_messageDispatcher);
	_systems.insert(std::make_pair(sceneManager->SysType, sceneManager));

	Logger::Instance().LogMessage("Initalising Graphics system", LogSeverity::eInfo);
	auto graphics = make_shared<TestGraphics>(_messageDispatcher); // Create a test graphics instance for now
	_systems.insert(std::make_pair(graphics->SysType, graphics));

	Logger::Instance().LogMessage("Initalising InputHandler system", LogSeverity::eInfo);
	auto inputHandler = make_shared<InputHandler>(_messageDispatcher);
	_systems.insert(std::make_pair(inputHandler->SysType, inputHandler));

	Logger::Instance().LogMessage("Initalising SceneSaver system", LogSeverity::eInfo);
	auto sceneSaverSystem = make_shared<SceneSaver>(_messageDispatcher);
	_systems.insert(std::make_pair(sceneSaverSystem->SysType, sceneSaverSystem));

	Logger::Instance().LogMessage("Initalising Physics system", LogSeverity::eInfo);
	auto physicsSystem = make_shared<PhysicsSystem>(_messageDispatcher);
	_systems.insert(std::make_pair(physicsSystem->SysType, physicsSystem));
}

// If any of the systems are listening for message this function sets it up. Called after system initalisation.
void Engine::InitaliseListeners()
{
	for (auto s : _systems)
	{
		s.second->InitaliseListeners();
	}
}

// This is a simple callback for each system after every system has been intialised with listeners
void Engine::SystemsInitalised()
{
	for (auto s : _systems)
	{
		s.second->SystemsInitalised();
	}
}

std::shared_ptr<ISystem> Engine::GetSystem(SystemType type)
{
	return _systems.at(type);
}