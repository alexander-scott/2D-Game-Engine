#include "Engine.h"

#include "BuildSceneMessage.h"
#include "RequestBuildSceneMessage.h"

// Constructor that uses width and height from Consts.h
Engine::Engine() : ISystem(SystemType::eEngine)
{
	_lastTime = std::chrono::steady_clock::now();
	_lag = 0;
}

// Constructor that uses width and height that are passed in from MainWindow.h
Engine::Engine(int width, int height) : ISystem(SystemType::eEngine)
{
	_lastTime = std::chrono::steady_clock::now();
	_lag = 0;
}

Engine::~Engine()
{

}

void Engine::UpdateEngine()
{
	auto currentTime = std::chrono::steady_clock::now();
	const std::chrono::duration<float> elapsedTime = currentTime - _lastTime;
	_lastTime = currentTime;
	_lag += elapsedTime.count();

	// ProcessInput()

	while (_lag >= MS_PER_UPDATE)
	{
		// ProcessPhysics()
		
		// Update the current scene in the SceneManager system
		SystemMessageDispatcher::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eUpdateScene));

		_lag -= MS_PER_UPDATE;
	}

	// Tell the Graphics system to begin the frame
	SystemMessageDispatcher::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsStartFrame));

	// Draw the current scene in the SceneManager system
	SystemMessageDispatcher::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eDrawScene));

	// Tell the Graphics system to end the frame
	SystemMessageDispatcher::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsEndFrame));
}

void Engine::RecieveMessage(ISystemMessage& message)
{
	if (message.Type == SystemMessageType::eWindowUpdate)
	{
		UpdateEngine();
	}
}

void Engine::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eWindowUpdate);
}

void Engine::SystemsInitalised()
{
	// Request graphics initalised
	SystemMessageDispatcher::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsRequestInitalise));

	// Request a new scene be built by the SceneBuilder system
	RequestBuildSceneMessage message("..\\Resources\\Scenes\\Scene1.xml"); // Hardcoded for now
	SystemMessageDispatcher::Instance().SendMessageToListeners(message);
}