#pragma once

#include "SystemMessageDispatcher.h"

#include "ISystem.h"

using namespace std;

class Engine : public ISystem
{
public:
	Engine();
	Engine(int width, int height);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void RecieveMessage(ISystemMessage& message) override;

	~Engine();

private:
	void EngineUpdateLoop();
	void InitaliseEngine();
};