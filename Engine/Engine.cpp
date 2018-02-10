#include "Engine.h"

#include "BuildSceneMessage.h"

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
	SubscribeToMessageType(MessageType::eBuildSceneMessage);

	// Request a new scene be built by the SceneBuilder system
	PostOffice::Instance().SendMessageToListeners(IMessage(MessageType::eRequestBuildSceneMessage));
}

void Engine::RecieveMessage(IMessage & message)
{
	if (message.Type == MessageType::eBuildSceneMessage)
	{
		// Set the scene built by the SceneBuilder system as the current scene
		BuildSceneMessage& msg = static_cast<BuildSceneMessage&>(message);
		_currentScene = msg.GetScene();
	}
}

void Engine::Update()
{
	// Tell the Graphics system to begin the frame
	PostOffice::Instance().SendMessageToListeners(IMessage(MessageType::eGraphicsStartFrame));

	UpdateScene();
	DrawScene();

	// Tell the Graphics system to end the frame
	PostOffice::Instance().SendMessageToListeners(IMessage(MessageType::eGraphicsEndFrame));
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