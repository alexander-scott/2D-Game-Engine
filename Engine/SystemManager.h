#pragma once

#include "ISystem.h"

#include "MainWindow.h"

class SystemManager
{
public:
	SystemManager(HINSTANCE hInst, wchar_t * pArgs);
	~SystemManager();

	bool SystemUpdate();

private:
	void InitaliseSystems(HINSTANCE hInst, wchar_t * pArgs);
	void InitaliseListeners();
	void SystemsInitalised();

	std::shared_ptr<SystemMessageDispatcher>			_messageDispatcher;

	std::shared_ptr<MainWindow>							_mainWindow;
	std::map<SystemType, std::shared_ptr<ISystem>>		_systems;
};