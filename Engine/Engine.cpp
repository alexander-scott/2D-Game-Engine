#include "Engine.h"

#include "BuildSceneMessage.h"
#include "RequestBuildSceneMessage.h"

// Constructor that uses width and height from Consts.h
Engine::Engine(std::shared_ptr<SystemMessageDispatcher> dispatcher) 
	: ISystem(SystemType::eEngine, dispatcher)
{
	_lastTime = std::chrono::steady_clock::now();
	_lag = 0;
}

// Constructor that uses width and height that are passed in from MainWindow.h
Engine::Engine(int width, int height, std::shared_ptr<SystemMessageDispatcher> dispatcher) 
	: ISystem(SystemType::eEngine, dispatcher)
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

	// This while loop processes scene updates and physics at a fixed rate.
	// Whilst allowing graphics to render as fast as possible.
	while (_lag >= MS_PER_UPDATE)
	{
		// ProcessPhysics()
		
		// Update the current scene in the SceneManager system
		SendMessageToDispatcher(ISystemMessage(SystemMessageType::eUpdateScene));

		_lag -= MS_PER_UPDATE;
	}

	// Tell the Graphics system to begin the frame
	SendMessageToDispatcher(ISystemMessage(SystemMessageType::eGraphicsStartFrame));

	// Draw the current scene in the SceneManager system
	SendMessageToDispatcher(ISystemMessage(SystemMessageType::eDrawScene));

	// Tell the Graphics system to end the frame
	SendMessageToDispatcher(ISystemMessage(SystemMessageType::eGraphicsEndFrame));
}

void Engine::RecieveMessage(ISystemMessage& message)
{
	if (message.Type == SystemMessageType::eSystemUpdate)
	{
		UpdateEngine();
	}
}

void Engine::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eSystemUpdate);
}

void Engine::SystemsInitalised()
{
	// Request a new scene be built by the SceneBuilder system
	RequestBuildSceneMessage message("..\\Resources\\Scenes\\Scene1.xml"); // Hardcoded for now
	SendMessageToDispatcher(message);
}