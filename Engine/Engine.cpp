#include "Engine.h"

#include "BuildSceneMessage.h"

// Constructor that uses width and height from Consts.h
Engine::Engine()
{
	InitaliseEngine();
}

// Constructor that uses width and height that are passed in from MainWindow.h
Engine::Engine(int width, int height)
{
	InitaliseEngine();
}

Engine::~Engine()
{

}

void Engine::InitaliseEngine()
{
	// Request a new scene be built by the SceneBuilder system
	SystemMessageDispatcher::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eRequestBuildSceneMessage));
}

void Engine::Update()
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