#pragma once

#include "ISystem.h"

#include <chrono>

class MainWindow;

class Engine
{
public:
	Engine(HWND hWnd);
	Engine(HINSTANCE hInst, wchar_t * pArgs);
	~Engine();

	void StartUpdateLoop();

	std::shared_ptr<ISystem> GetSystem(SystemType type);

private:
	void InitaliseSystems();
	void InitaliseListeners();
	void SystemsInitalised();

	std::shared_ptr<SystemMessageDispatcher>			_messageDispatcher;

	std::shared_ptr<MainWindow>							_mainWindow;
	std::map<SystemType,std::shared_ptr<ISystem>>		_systems;

	float												_lag;
	std::chrono::steady_clock::time_point				_lastTime;
};