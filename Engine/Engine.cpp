#include "Engine.h"

#include "BuildSceneMessage.h"
#include "InitaliseGraphicsMessage.h"

// Constructor that uses width and height from Consts.h
Engine::Engine(MainWindow & wnd) : _mainWindow(wnd)
{
	InitaliseEngine();
}

// Constructor that uses width and height that are passed in from MainWindow.h
Engine::Engine(MainWindow& wnd, int width, int height) : _mainWindow(wnd)
{
	InitaliseEngine();
}

Engine::~Engine()
{

}

void Engine::InitaliseEngine()
{
	// Initalise Graphics system
	PostOffice::Instance().SendMessageToListeners(InitaliseGraphicsMessage(_mainWindow));

	// Request a new scene be built by the SceneBuilder system
	PostOffice::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eRequestBuildSceneMessage));
}

void Engine::Update()
{
	// Tell the Graphics system to begin the frame
	PostOffice::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsStartFrame));

	// Update the current scene in the SceneManager system
	PostOffice::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eUpdateScene));

	// Draw the current scene in the SceneManager system
	PostOffice::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eDrawScene));

	// Tell the Graphics system to end the frame
	PostOffice::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsEndFrame));
}