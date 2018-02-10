#pragma once

#include "MainWindow.h"

#include "PostOffice.h"

#include "SystemManager.h"

using namespace std;

class Engine
{
public:
	Engine(class MainWindow& wnd);
	Engine(class MainWindow& wnd, int width, int height);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void Update();

	~Engine();

private:
	void InitaliseEngine();

	MainWindow&				_mainWindow;
	SystemManager			_systemsManager;
};