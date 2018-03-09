#pragma once

#include "FrameTimer.h"

#include "Scene.h"

#include "ISystem.h"

class SceneManager : public ISystem
{
public:
	SceneManager(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;

	void RecieveMessage(ISystemMessage& message) override;

	//TODO ?: Add method Draw that populates the DrawSceneMessage sent to the Graphics

	shared_ptr<Scene> GetScene() { return _currentScene; }

private:
	shared_ptr<Scene>		_currentScene;
	FrameTimer				_frameTimer;
	bool					_isPlaying;
};