#pragma once

#include "FrameTimer.h"

#include "IScene.h"

#include "ISystem.h"

class SceneManager : public ISystem
{
public:
	SceneManager(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;

	void RecieveMessage(ISystemMessage& message) override;

private:
	shared_ptr<IScene>		_currentScene;
	FrameTimer				_frameTimer;
};