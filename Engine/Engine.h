#pragma once

#include "ISystem.h"
#include "Logger.h"

#include <chrono>

class MainWindow;

class Engine
{
public:
	Engine();
	Engine(HWND hWnd);
	Engine(HINSTANCE hInst, wchar_t * pArgs);
	~Engine();

	void StartUpdateLoop();

	std::shared_ptr<ISystem> GetSystem(SystemType type);

protected:
	void Initalise();

	virtual void InitaliseSystems(); // Virtual to override in unit tests
	void InitaliseListeners();
	void SystemsInitalised();

	virtual bool UpdateLoop(); // Virtual to access in unit tests

	std::shared_ptr<SystemMessageDispatcher>			_messageDispatcher;

	std::shared_ptr<MainWindow>							_mainWindow;
	std::map<SystemType,std::shared_ptr<ISystem>>		_systems;

	float												_deltaTime;
	std::chrono::steady_clock::time_point				_lastTime;
};