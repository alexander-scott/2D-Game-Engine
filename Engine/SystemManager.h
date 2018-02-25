#pragma once

#include "ISystem.h"

#include "MainWindow.h"

class SystemManager
{
public:
	SystemManager(HWND hWnd);
	SystemManager(HINSTANCE hInst, wchar_t * pArgs);
	~SystemManager();

	void StartUpdateLoop();

private:
	void InitaliseSystems();
	void InitaliseListeners();
	void SystemsInitalised();

	std::shared_ptr<SystemMessageDispatcher>			_messageDispatcher;

	std::shared_ptr<MainWindow>							_mainWindow;
	std::map<SystemType,std::shared_ptr<ISystem>>		_systems;
};