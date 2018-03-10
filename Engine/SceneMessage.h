#pragma once

#include "ISystemMessage.h"

class Scene;

class SceneMessage : public ISystemMessage
{
public:
	SceneMessage(SystemMessageType type, std::shared_ptr<Scene> scene) : ISystemMessage(type)
	{
		_scene = scene;
	}

	std::shared_ptr<Scene> GetScene() { return _scene; }

private:
	std::shared_ptr<Scene>		_scene;
};