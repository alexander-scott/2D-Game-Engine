#include "Engine.h"

#include "RequestBuildScene.h"
#include "BuildSceneMessage.h"

// Constructor that uses width and height from Consts.h
Engine::Engine(MainWindow & wnd) : _mainWindow(wnd), PostOfficeMessenger(MessengerType::eEngineMessenger)
{
	InitaliseEngine();
}

// Constructor that uses width and height that are passed in from MainWindow.h
Engine::Engine(MainWindow& wnd, int width, int height) : _mainWindow(wnd), PostOfficeMessenger(MessengerType::eEngineMessenger)
{
	InitaliseEngine();
}

Engine::~Engine()
{

}

void Engine::InitaliseEngine()
{
	PostOffice::Instance().AddListener(this, MessageType::eBuildSceneMessage);

	RequestBuildScene buildMsg;
	PostOffice::Instance().SendMessageToListeners(buildMsg);
}

void Engine::RecieveMessage(IMessage & message)
{
	if (message.Type == MessageType::eBuildSceneMessage)
	{
		BuildSceneMessage& msg = static_cast<BuildSceneMessage&>(message);
		_currentScene = msg.GetScene();
	}
}

void Engine::Update()
{
	// BEGIN FRAME

	UpdateScene();
	DrawScene();

	// END FRAME
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