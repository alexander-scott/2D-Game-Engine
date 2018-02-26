#pragma once

#include <chrono>

#include "ISystem.h"

using namespace std;

class Engine : public ISystem
{
public:
	Engine(std::shared_ptr<SystemMessageDispatcher> dispatcher);
	Engine(int width, int height, std::shared_ptr<SystemMessageDispatcher> dispatcher);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void RecieveMessage(ISystemMessage& message) override;
	void InitaliseListeners() override;

	~Engine();

private:
	void UpdateEngine();

	float									_lag;
	std::chrono::steady_clock::time_point	_lastTime;
};