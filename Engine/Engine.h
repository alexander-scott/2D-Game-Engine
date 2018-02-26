#pragma once

#include "ISystem.h"

#include "MainWindow.h"

#include <chrono>

// This class is simply a collection of all systems within the Engine.
// It also houses the main update loop, where update messages are sent to other systems in a specific order, at a specific interval.
class Engine
{
public:
	Engine(HINSTANCE hInst, wchar_t * pArgs);
	~Engine();

	bool Update();

private:
	void InitaliseSystems(HINSTANCE hInst, wchar_t * pArgs);
	void InitaliseListeners();
	void SystemsInitalised();

	std::shared_ptr<SystemMessageDispatcher>			_messageDispatcher;

	std::shared_ptr<MainWindow>							_mainWindow;
	std::map<SystemType, std::shared_ptr<ISystem>>		_systems;

	float												_lag;
	std::chrono::steady_clock::time_point				_lastTime;
};