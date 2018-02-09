#pragma once

#include "MainWindow.h"
#include "FrameTimer.h"

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
	MainWindow&				_mainWindow;
	FrameTimer				_frameTimer;
};