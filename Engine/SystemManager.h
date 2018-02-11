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
	~SystemManager();

	void InitaliseMainWindow(HINSTANCE hInst, wchar_t * pArgs);
	bool UpdateMainWindow();

	void InitaliseSystems();

	std::shared_ptr<ISystem> GetSystem(SystemType type);
	void AddSystem(shared_ptr<ISystem> system, SystemType type);

private:
	shared_ptr<MainWindow>								_mainWindow;
	std::map<SystemType, std::shared_ptr<ISystem>>		_systems;
};