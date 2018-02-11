#include "Engine.h"

#include "BuildSceneMessage.h"
#include "RequestBuildSceneMessage.h"

// Constructor that uses width and height from Consts.h
Engine::Engine() : ISystem(SystemType::eEngine)
{
	InitaliseEngine();
}

// Constructor that uses width and height that are passed in from MainWindow.h
Engine::Engine(int width, int height) : ISystem(SystemType::eEngine)
{
	InitaliseEngine();
}

Engine::~Engine()
{

}

void Engine::InitaliseEngine()
{
	// Request graphics initalised
	SystemMessageDispatcher::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsRequestInitalise));

	// Request a new scene be built by the SceneBuilder system
	RequestBuildSceneMessage message("..\\Resources\\Scenes\\Scene1.xml"); // Hardcoded for now
	SystemMessageDispatcher::Instance().SendMessageToListeners(message);

	// Start the update loop
	EngineUpdateLoop(); 
}

void Engine::EngineUpdateLoop()
{
	while (true) // TODO: Change this to update at a select interval, say 60fps
	{
		// Tell the Graphics system to begin the frame
		SystemMessageDispatcher::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsStartFrame));

		// Update the current scene in the SceneManager system
		SystemMessageDispatcher::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eUpdateScene));

		// Draw the current scene in the SceneManager system
		SystemMessageDispatcher::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eDrawScene));

		// Tell the Graphics system to end the frame
		SystemMessageDispatcher::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsEndFrame));
	}
}

void Engine::RecieveMessage(ISystemMessage& message)
{
	// No messages to recieve yet
}