#pragma once

#include "ISystemMessage.h"

class Scene;

class BuildSceneMessage : public ISystemMessage
{
public:
	BuildSceneMessage(shared_ptr<Scene> scene) : ISystemMessage(SystemMessageType::eBuildSceneMessage), _scene(scene) { }

	shared_ptr<Scene> GetScene() { return _scene; }

private:
	shared_ptr<Scene>		_scene;
};