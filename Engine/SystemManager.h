#pragma once

#include "Consts.h"

#include "ISystem.h"

#include "MainWindow.h"

#include "Engine.h"
#include "SceneBuilder.h"
#include "SceneManager.h"
#include "TestGraphics.h"

class SystemManager
{
public:
	SystemManager(HINSTANCE hInst, wchar_t * pArgs);
	~SystemManager();

	bool SystemUpdate();

	std::shared_ptr<ISystem> GetSystem(SystemType type);
	void AddSystem(shared_ptr<ISystem> system, SystemType type);

private:
	void InitaliseSystems(HINSTANCE hInst, wchar_t * pArgs);
	void InitaliseListeners();
	void SystemsInitalised();

	shared_ptr<MainWindow>								_mainWindow;
	std::map<SystemType, std::shared_ptr<ISystem>>		_systems;
};