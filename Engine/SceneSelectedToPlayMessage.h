#pragma once

#include "ISystemMessage.h"

class Scene;

class SceneSelectedToPlayMessage : public ISystemMessage
{
public:
	SceneSelectedToPlayMessage(std::shared_ptr<Scene> scene) : ISystemMessage(SystemMessageType::eSceneSelectedToPlay)
	{
		_scene = scene;
	}

	std::shared_ptr<Scene> GetScene() { return _scene; }

private:
	std::shared_ptr<Scene>		_scene;
};