#pragma once

#include "MainWindow.h"

using namespace std;

class Engine
{
public:
	Engine(class MainWindow& wnd, int width, int height);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void Update();

	~Engine();

	MainWindow& wnd;
};