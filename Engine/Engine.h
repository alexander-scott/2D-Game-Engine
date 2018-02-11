#pragma once

#include "PostOffice.h"

#include "SystemManager.h"

using namespace std;

class Engine
{
public:
	Engine();
	Engine(int width, int height);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void Update();

	~Engine();

private:
	void InitaliseEngine();

	SystemManager			_systemsManager;
};