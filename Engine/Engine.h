#pragma once

#include "MainWindow.h"
#include "FrameTimer.h"

#include "IScene.h"

#include "PostOfficeListener.h"
#include "PostOffice.h"

#include "SystemManager.h"

using namespace std;

class Engine : public PostOfficeListener
{
public:
	Engine(class MainWindow& wnd);
	Engine(class MainWindow& wnd, int width, int height);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void RecieveMessage(IMessage& message) override;
	void Update();

	~Engine();

private:
	void InitaliseEngine();

	void DrawScene();
	void UpdateScene();

	MainWindow&				_mainWindow;
	FrameTimer				_frameTimer;
	SystemManager			_systemsManager;

	shared_ptr<IScene>		_currentScene;
};