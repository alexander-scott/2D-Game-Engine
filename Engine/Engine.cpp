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
	// Add a listener for when the new scene gets built
	SubscribeToMessageType(SystemMessageType::eBuildSceneMessage);

	// Initalise Graphics system
	PostOffice::Instance().SendMessageToListeners(InitaliseGraphicsMessage(_mainWindow));

	// Request a new scene be built by the SceneBuilder system
	PostOffice::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eRequestBuildSceneMessage));
}

void Engine::RecieveMessage(ISystemMessage & message)
{
	if (message.Type == SystemMessageType::eBuildSceneMessage)
	{
		// Set the scene built by the SceneBuilder system as the current scene
		BuildSceneMessage& msg = static_cast<BuildSceneMessage&>(message);
		_currentScene = msg.GetScene();
	}
}

void Engine::Update()
{
	// Tell the Graphics system to begin the frame
	PostOffice::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsStartFrame));

	UpdateScene();
	DrawScene();

	// Tell the Graphics system to end the frame
	PostOffice::Instance().SendMessageToListeners(ISystemMessage(SystemMessageType::eGraphicsEndFrame));
}

void Engine::DrawScene()
{
	if (_currentScene == nullptr)
		return;

	_currentScene->Draw();
}

void Engine::UpdateScene()
{
	if (_currentScene == nullptr)
		return;

	float deltaTime = _frameTimer.Mark();
	_currentScene->Update(deltaTime);
}